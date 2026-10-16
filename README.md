# ENV PRO Firmware (M5Stack AtomS3 Lite)

This repository contains the official firmware source code for the ENV PRO environmental monitor, designed for the M5Stack AtomS3 Lite using the Bosch BME688 sensor and BSEC2 library. It provides a minimal, self‑contained environmental telemetry endpoint running in Wi‑Fi Access Point mode, serving a lightweight HTML dashboard.

This GitHub repository exists solely as the canonical engineering source for the firmware. All higher‑level documentation, LLM reasoning, datasets, and prosumer materials are published on Hugging Face.

---

## Features

- BME688 sensor via I²C  
- Bosch BSEC2 environmental outputs  
- Temperature, humidity, pressure  
- Gas resistance, CO₂ equivalent, VOC equivalent  
- IAQ + accuracy  
- Local Wi‑Fi AP dashboard (auto‑refreshing)  
- Serial debug output  
- Arduino IDE 1.8.19 build environment

---

## Firmware

The repository includes:

```
firmware/
    env_pro_firmware.ino
    env_pro_firmware.bin
```

The `.bin` file is provided for convenience and reproducibility.  
It contains the same default AP password used in the source code.  
This password is not a sensitive credential and is safe to publish, as the device operates only in local AP mode.

---

## Bosch Documentation

ENV PRO uses the official Bosch Sensortec BME688 sensor and BSEC2 software library.  
For authoritative definitions of IAQ, CO₂eq, VOCeq, raw gas resistance, and other outputs, refer to:

- BME688 Datasheet  
- BSEC2 Software Library Documentation  
- BSEC2 Integration Guide  

These documents are available from Bosch Sensortec’s official website.

---

## Hugging Face

The ENV PRO inference stack — including GGUF model files, the Docker inference environment, Colab test notebooks, and supporting Python code (app.py, requirements.txt) — is published on Hugging Face:

**https://huggingface.co/Jonathan/ENV-PRO**

This GitHub repository contains only the firmware source for the M5Stack S3 Lite sensor endpoint.

## License

MIT License

Copyright (c) 2026 EdgeTechSensors38 and contributors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE

---

## Project Links

- Firmware (GitHub) — this repository  
- LLM, datasets, APK, Docker, notebooks (Hugging Face) — full ENV PRO reasoning system
