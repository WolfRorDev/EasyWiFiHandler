# Simple Wi-Fi for ESP8266 EN
## Description
This script was created to support a Wi-Fi module (e.g. ESP8266) in conjunction with other devices such as STM32 or Arduino. It allows you to quickly and easily connect to a Wi-Fi network and send a GET request, the value of which will be returned to the microcontroller (e.g. STM32, Arduino)

## Requirements
### Electronics
- Wi-Fi module with ESP processor, e.g. ESP-01S
- ESP to USB adapter (UART communication)

### Software
- Arduino IDE
- Downloaded firmware for ESP8266 processors
   - The following link should be pasted into the Arduino IDE configuration, in the section ``Additional URLs to the board manager:``
   - Link: ``https://arduino.esp8266.com/stable/package_esp8266com_index.json``

## Commands
### Wi-Fi setup
To configure Wi-Fi, enter the command `set -nt:<number of attempts> -ssid:<ssid> -pass:<password> -hostname:<device name> -ar:<autoconnect>` with the following parameters. The order of the parameters does not matter. You can't put everything on one line.
- `<number of attempts>` - The number of attempts after which, in the absence of connection to the Wi-Fi network, the `WE1` message will be returned. Default 10
- `<ssid>` - Wi-Fi network name
- `<password>` - Wi-Fi network password
- `<hostname>` - Device name that will be visible on network devices (ap, router). Default "ESP"
- `<automatic connection>` - Automatic connection to the wi-fi network after losing the connection. 1 - Yes, 0 - No. Default NO

Example use of the command:
- `` set -nt:10 -ssid:githubWifi -pass:password1234 -hostname:GitHub -ar:1 ``
- `` set -nt:10 -ssid:githubWifi -pass:password1234 -hostname:GitHub ``
- `` set -nt:10 -ssid:githubWifi -pass:password1234 ``
- `` set -hostname:GitHub -ssid:githubWifi -pass:password1234 ``

Sample answers:
- Correct answer ``WS3: Parameters has been set``
- Invalid response ``WE5: Cannot change parameters. Wi-Fi connection is active``

### Wi-Fi connection
In order to connect the module to the Wi-Fi network, enter the ``conn`` command.

Sample answers:
- Correct answer ``WS3: Connected to a Wi-Fi network``
- Correct answer ``WS2:
   SSID: githubWifi
   Auto reconnect: True
   IP address: 192.168.0.200
   Mac: 00:00:00:00:00:00
   Hostname: GitHub``
- Incorrect response ``WE6: Parameters to connect are missing``
- Incorrect response ``WE1: Failed to connect``

### Checking the connection
In order to check the connection, enter the ``get`` command.

Sample answers
- Correct answer ``WS2:
   SSID: githubWifi
   Auto reconnect: True
   IP address: 192.168.0.200
   Mac: 00:00:00:00:00:00
   Hostname: GitHub``

### Disconnecting from a Wi-Fi network
In order to disconnect the module from Wi-Fi, enter the ``close`` command.

Sample answers
- The correct answer is ``WS3: Wi-Fi Disconnected``

### Checking the SSID
If the module is connected to the Wi-Fi network, you can check the ssid using the ``ssid`` command or using the ``get`` command described earlier

Sample answers
- The correct answer is ``WS4: SSID: githubWifi``

### Checking the IP address
If the module is connected to the Wi-Fi network, you can check the ip address using the ``ip`` command

Sample answers
- Correct answer ``WS4: IP: 192.168.0.200``

### Download page content
In order to send a get request, enter the address of the website.

Example use of the command:
- ``http://192.168.0.201``
- ``http://wolfror.com``
- ``https://wolfror.com``
- ``https://google.com``

Answers:
- Correct answer - the module will return a text version of the website
- Incorrect response ``WE4: HTTP request error``

### Invalid command
If an incorrect command is entered, 2 messages may appear.
- Module connected to Wi-Fi ``WE3: Invalid command``
- Module not connected to Wi-Fi ``WE2: No connection to Wi-Fi``

## Answer table
| Message code | Message description |
| ----- | ----- |
| WS1 | Connection Status |
| WS2 | Connection settings |
| WS3 | Request confirmation |
| WS4 | Status of the setting |

## Error table
| Error code | Error description |
| ----- | -----|
| WE1 | Failed to connect |
| WE2 | No connection to Wi-Fi |
| WE3 | Invalid command |
| WE4 | HTTP request error |
| WE5 | Cannot change parameters. Wi-Fi connection is active |
| WE6 | Parameters to connect are missing |
 
## Author information
The creator of the script is Dominik Krzywański.<br>
Creator's website: [WolfRor](https://wolfror.com)
---


# Proste Wi-Fi dla ESP8266 PL
## Opis
Ten skrypt został stworzony w celu obsługi modułu Wi-Fi (np. ESP8266) w połączeniu z innymi urządzeniami, takimi jak STM32 czy Arduino. Umożliwia szybkie i łatwe nawiązywanie połączeń z siecią Wi-Fi oraz wysłanie zapytania GET, którego wartość zostanie zwrócona do mikrokontrolowe (np. STM32, Arduino)

## Wymagania
### Elektronika
- Moduł Wi-Fi z procesorem ESP np. ESP-01S
- Adapter ESP do usb (Komunikacja po uart)

### Oprogramowanie
- Arduino IDE
- Pobrane oprogramowanie dla procesorów ESP8266
  - Poniższy link należy wkleić do konfiguracji Arduino IDE, w sekcji ``Dodatkowe adresy URL do menedżera płytek:``
  - Link: ``https://arduino.esp8266.com/stable/package_esp8266com_index.json``

## Komendy
### Konfiguracja Wi-Fi
W celu skonfigurowania Wi-Fi należy wpisać komendę `set -nt:<liczb prób> -ssid:<ssid> -pass:<hasło> -hostname:<nazwa urządzenia> -ar:<podłaczenie automatyczne>` z następującymi paramatrami. Kolejność parametrów nie ma znaczenia. Można nie podawać wszyskiego w jednej linii.
- `<liczba prób>` - Liczba po prób po której, w przypadku braku połączenia do sieci Wi-Fi zostanie zwrócony komunikat `WE1`. Domyślnie 10
- `<ssid>` - Nazwa sieci Wi-Fi
- `<hasło>` - Hasło do sieci Wi-Fi
- `<hostname>` - Nazwa urządzenie, która będzie widoczna na urządzeniach sieciowych (ap, router). Domyślnie "ESP"
- `<podłaczenie automatyczne>` - Automatyczne podłączenie do sieci wi-fi po utracie połączenia. 1 - Tak, 0 - Nie. Domyślnie NIE

Przykładowe użycie komendy:
- `` set -nt:10 -ssid:githubWifi -pass:password1234 -hostname:GitHub -ar:1 ``
- `` set -nt:10 -ssid:githubWifi -pass:password1234 -hostname:GitHub ``
- `` set -nt:10 -ssid:githubWifi -pass:password1234 ``
- `` set -hostname:GitHub -ssid:githubWifi -pass:password1234 ``

Przykładowe odpowiedzi:
- Poprawna odpowiedź ``WS3: Parameters has been set``
- Błędna odpowiedź ``WE5: Cannot change parameters. Wi-Fi connection is active``

### Połączenie z Wi-Fi
W celu połączenia modułu z siecią Wi-Fi należy wpisać komendę ``conn``. 

Przykładowe odpowiedzi:
- Poprawna odpowiedź ``WS3: Connected to a Wi-Fi network``
- Poprawna odpowiedź ``WS2:
  SSID: githubWifi
  Auto reconnect: True
  IP address: 192.168.0.200
  Mac: 00:00:00:00:00:00
  Hostname: GitHub``
- Błędna odpowiedź ``WE6: Parameters to connect are missing``
- Błędna odpowiedź ``WE1: Failed to connect``

### Sprawdzenie połączenia
W celu sprawdzenia połączenia należy wpisać komendę ``get``.

Przykładowe odpowiedzi
- Poprawna odpowiedź ``WS2:
  SSID: githubWifi
  Auto reconnect: True
  IP address: 192.168.0.200
  Mac: 00:00:00:00:00:00
  Hostname: GitHub``

### Rozłączanie z siecią Wi-Fi
W celu rozłączenia modułu z Wi-Fi należy wpisać komendę ``close``.

Przykładowe odpowiedzi
- Poprawna odpowiedź ``WS3: Wi-Fi Disconnected``

### Sprawdzanie SSID
Jeżeli moduł jest podłączony do sieci Wi-Fi można sprawdzić ssid przy pomocy komendy ``ssid`` albo przy użyciu wcześniej opisanej komendy ``get``

Przykładowe odpowiedzi
- Poprawna odpowiedź ``WS4: SSID: githubWifi``

### Sprawdzanie adresu IP
Jeżeli moduł jest podłączony do sieci Wi-Fi można sprawdzić adres ip przy pomocy komendy ``ip``

Przykładowe odpowiedzi
- Poprawna odpowiedź ``WS4: IP: 192.168.0.200``

### Pobranie zawartości strony
W celu wysłania zapytania get należy wpisać adres strony.

Przykładowe użycie komendy:
- ``http://192.168.0.201``
- ``http://wolfror.com``
- ``https://wolfror.com``
- ``https://google.com``

Odpowiedzi:
- Poprawna odpowiedź - moduł zwróci stronę internetową w wersji tekstowej
- Błędna odpowiedź ``WE4: HTTP request error``

### Błędna komenda
W przypadku wpisania błędnej komendy mogą wystąpić 2 komunikaty.
- Moduł podłaczony do Wi-Fi ``WE3: Invalid command``
- Moduł nie podłaczony do Wi-Fi ``WE2: No connection to Wi-Fi``

## Tabela odpowiedzi
| Kod wiadomości | Opis wiadomości |
| ----- | ----- |
| WS1 | Status połączenia |
| WS2 | Ustawienia połaczenia |
| WS3 | Potwierdzenie żądania |
| WS4 | Status danego ustawienia |

## Tabela błędów
| Kod błędu | Opis błędu |
| ----- | -----|
| WE1 | Nie udało się połączyć |
| WE2 | Brak połaczenia do Wi-FI |
| WE3 | Błędna komenda |
| WE4 | Błąd żądania HTTP |
| WE5 | Nie można zmienić parametrów. Połączenie Wi-Fi jest aktywne |
| WE6 | Brak parametrów do połączenia |

## Informacje o autorze
Twórcą skryptu jest Dominik Krzywański. <br>
Witryna twórcy: [WolfRor](https://wolfror.com)
