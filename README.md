### Projeto ESP32-S3 com Dual nRF24L01+PA+LNA 📡🤖

Este repositório contém a documentação de hardware e o código de teste para conectar e controlar **dois módulos transceptores nRF24L01+PA+LNA** de forma simultânea utilizando um único microcontrolador **ESP32-S3 (Modelo N18R8 - 16MB Flash / 8MB PSRAM Octal)**. O ambiente de desenvolvimento utilizado é o **VS Code com PlatformIO no Ubuntu Linux**. 

### 🛠️ Especificações de Hardware & Componentes

* **Microcontrolador:** ESP32-S3 N18R8 (Pinos soldados de fábrica).
* **Módulos de Rádio:** 2x nRF24L01+PA+LNA com antena externa.
* **Placa Adaptadora:** Placa de expansão para nRF24L01 (Desenhada originalmente para ESP32 DevKitC clássico de 38 pinos).

### ⚙️ Configuração do Ambiente (PlatformIO)

Substitua o conteúdo do seu arquivo platformio.ini localizado na raiz do projeto para configurar corretamente a memória Octal e gerenciar a dependência da biblioteca RF24 de forma automática: 

```bash
[env:esp32-s3-devkitc-1]
platform = espressif32
board = esp32-s3-devkitc-1
framework = arduino
monitor_speed = 115200

; Configurações para o ESP32-S3 N18R8 (16MB Flash / 8MB PSRAM Octal)
board_upload.flash_size = 16MB
board_build.partitions = default_16MB.csv
build_flags = 
    -DBOARD_HAS_PSRAM
    -mfix-esp32-psram-cache-issue
    -DARDUINO_USB_CDC_ON_BOOT=0    ; Redireciona o Monitor Serial para a USB nativa do S3

; Configuração das memórias em modo QIO (Flash) e OPI (PSRAM Octal)
board_build.arduino.memory_type = qio_opi

; Dependência automática de Bibliotecas
lib_deps =
    nRF24/RF24 @ ^1.6.2
```

### 🐧 Dica para Usuários Ubuntu Linux

Se o PlatformIO encontrar problemas de permissão para gravar na placa através de portas como **/dev/ttyACM0** ou **/dev/ttyUSB0**, execute o seguinte comando no terminal do Ubuntu para adicionar seu usuário ao grupo de comunicação serial (será necessário reiniciar o sistema após a execução): 

```bash
sudo usermod -aG dialout $USER
```

### 💻 Código-Fonte

Este código inicializa explicitamente o barramento SPI nos pinos seguros mapeados para o ESP32-S3 e configura ambos os rádios. O código está preparado para o modo de **Portadora Contínua (Continuous Carrier)** no Canal 100 (2500 MHz), ideal para testes de emissão de RF em bancada com analisadores de espectro. 

## 📌 Guia de Conexão Física (Mapeamento de Pinos)

### Pinagem ESP32-S3 ↔ Placa Suporte nRF24L01 (dupla)

Como a placa adaptadora original possui furação incompatível para o encaixe direto do ESP32-S3, utilizamos cabos jumper para criar uma ponte externa. O lado **Fêmea** conecta nos pinos do ESP32-S3 e o lado **Macho** é inserido com firmeza nos furos metalizados laterais da placa adaptadora. 

### Alimentação

| ESP32-S3 | Furo da placa suporte |
|----------|------------------------|
| 3V3      | VDD3                   |
| G        | GND                    |

### Rádio A — soquete direito

| ESP32-S3 | Furo da placa | Pino do nRF |
|----------|----------------|-------------|
| GPIO 12  | IO18           | SCK         |
| GPIO 13  | IO19           | MISO        |
| GPIO 11  | IO23           | MOSI        |
| GPIO 10  | IO21           | CSN         |
| GPIO 9   | IO22           | CE          |

### Rádio B — soquete esquerdo

| ESP32-S3 | Furo da placa | Pino do nRF |
|----------|----------------|-------------|
| GPIO 6   | IO14           | SCK         |
| GPIO 15  | IO12           | MISO        |
| GPIO 7   | IO13           | MOSI        |
| GPIO 5   | IO15           | CSN         |
| GPIO 4   | IO16           | CE          |

> **Nota:** pinagem válida especificamente para ESP32-S3-N16R8. Em outra variante do ESP32 (clássico, S2, C3 etc.) os GPIOs mudam, pois a S3 não possui os periféricos `HSPI`/`VSPI` com mapeamento fixo do ESP32 original.