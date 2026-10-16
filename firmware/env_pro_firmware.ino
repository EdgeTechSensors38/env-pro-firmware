#define ARDUINO_USB_CDC_ON_BOOT 1

#include <Arduino.h>
#include <Wire.h>
#include <bsec2.h>
#include <WiFi.h>
#include <WebServer.h>

Bsec2 env;
WebServer server(80);

float g_temp = NAN;
float g_hum = NAN;
float g_press = NAN;
float g_gas = NAN;
float g_co2 = NAN;
float g_voc = NAN;
int   g_iaqAcc = 0;

void startAP() {
    WiFi.mode(WIFI_AP);
    WiFi.softAP("ENV_MONITOR", "87650000");
    Serial.print("AP IP: ");
    Serial.println(WiFi.softAPIP());
}

String makePage() {
    String html = "<html><head><meta http-equiv='refresh' content='3'></head><body>";
    html += "<h3>Environmental Monitor</h3>";
    html += "Temp: " + String(g_temp, 2) + "<br>";
    html += "Hum: " + String(g_hum, 2) + "<br>";
    html += "Press: " + String(g_press, 2) + "<br>";
    html += "Gas: " + String(g_gas, 2) + "<br>";
    html += "CO2eq: " + String(g_co2, 2) + "<br>";
    html += "VOCeq: " + String(g_voc, 2) + "<br>";
    html += "IAQ accuracy: " + String(g_iaqAcc, 2) + "<br>";
    html += "</body></html>";
    return html;
}

void handleRoot() {
    server.send(200, "text/html", makePage());
}

void checkStatus(Bsec2 &b) {
    if (b.status < BSEC_OK) {
        Serial.printf("BSEC error: %d\n", b.status);
    } else if (b.status > BSEC_OK) {
        Serial.printf("BSEC warning: %d\n", b.status);
    }

    if (b.sensor.status < BME68X_OK) {
        Serial.printf("BME688 error: %d\n", b.sensor.status);
    } else if (b.sensor.status > BME68X_OK) {
        Serial.printf("BME688 warning: %d\n", b.sensor.status);
    }
}

void newDataCallback(const bme68xData data, const bsecOutputs outputs, Bsec2 b) {
    if (!outputs.nOutputs) return;

    for (uint8_t i = 0; i < outputs.nOutputs; i++) {
        const bsecData &o = outputs.output[i];

        switch (o.sensor_id) {
            case BSEC_OUTPUT_RAW_TEMPERATURE: g_temp = o.signal; break;
            case BSEC_OUTPUT_RAW_HUMIDITY:    g_hum = o.signal; break;
            case BSEC_OUTPUT_RAW_PRESSURE:    g_press = o.signal; break;
            case BSEC_OUTPUT_RAW_GAS: g_gas = o.signal; break;
            case BSEC_OUTPUT_CO2_EQUIVALENT:  g_co2 = o.signal; break;
            case BSEC_OUTPUT_BREATH_VOC_EQUIVALENT: g_voc = o.signal; break;
            case BSEC_OUTPUT_IAQ: g_iaqAcc = o.accuracy; break;
        }
    }

    Serial.printf("T=%.2f  H=%.2f  P=%.2f  Gas=%.2f  CO2=%.2f  VOC=%.2f  IAQacc=%d\n", g_temp, g_hum, g_press, g_gas, g_co2, g_voc, g_iaqAcc);
}

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("Booting… USB OK");

    Wire.begin(2, 1);
    Serial.println("I2C started on SDA=2, SCL=1");

    startAP();
    server.on("/", handleRoot);
    server.begin();

    if (!env.begin(BME68X_I2C_ADDR_HIGH, Wire)) {
        Serial.println("BSEC2 init failed — sensor missing?");
        checkStatus(env);
        while (true) {
            Serial.println("Waiting for sensor…");
            delay(1000);
        }
    }

    Serial.println("BSEC2 init OK");

    bsecSensor outputs[] = {
        BSEC_OUTPUT_IAQ,
        BSEC_OUTPUT_RAW_TEMPERATURE,
        BSEC_OUTPUT_RAW_HUMIDITY,
        BSEC_OUTPUT_RAW_PRESSURE,
        BSEC_OUTPUT_RAW_GAS,
        BSEC_OUTPUT_CO2_EQUIVALENT,
        BSEC_OUTPUT_BREATH_VOC_EQUIVALENT
    };

    if (!env.updateSubscription(outputs, ARRAY_LEN(outputs), BSEC_SAMPLE_RATE_LP)) {
        Serial.println("Subscription failed");
        checkStatus(env);
    }

    env.attachCallback(newDataCallback);

    Serial.printf("BSEC2 version: %d.%d.%d.%d\n",
                  env.version.major,
                  env.version.minor,
                  env.version.major_bugfix,
                  env.version.minor_bugfix);
}

void loop() {
    if (!env.run()) {
        checkStatus(env);
    }
    server.handleClient();
}
