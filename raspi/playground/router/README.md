### Введение
Ниже приведено описание процесса настройки raspberry в качестве wifi роутера.

### 1. Минимальный набор программ для настройки raspberry в качестве роутера:

- iw - работа с wifi;
- iptables - утилита для настройки межсетевого экрана (МЭ);
- hostapd - приложение для создания точек доступа wifi;
- isc-dhcp - утилита для настройки dhcp сервера;
- wvdial - программа для настройки доступа в интернет (опционально)

### 2. Установка

- sudo apt-get install iw iptables hostapd isc-dhcp wvdial

**NOTE:** перед установкой необходимо поверить наличие вышеуказанных пакетов:
- [packet-name] --version
- dpkg -s [packet-name]

### 3. Сетевые настройки

#### Для разрешения пересылки IPv4 пакетов между сетеями, а также запрет IPv6 нужно в
файле **sudo vim /etc/sysctl.conf** добавить:

```
net.ipv4.ip_forward=1
net.ipv6.conf.all.disable_ipv6 = 1
net.ipv6.conf.default.disable_ipv6 = 1
net.ipv6.conf.lo.disable_ipv6 = 1
net.ipv4.conf.default.rp_filter = 1
net.ipv4.conf.all.rp_filter = 1
```

#### Для "горячего" подключения нужно:
- sudo vim /etc/network/interfaces

	allow-hotplug [interface-name]

	iface [interface-name] inet manual

**Example:**
```
	allow-hotplug wlan0

	iface wlan0 inet manual
```

#### Необходимо задать статический адрес для интерфейса:
- sudo vim /etc/dhcpcd.conf

	interface [interface-name]

	static ip_address=192.168.1.1/24

**Example:**
	interface wlan0

	static ip_address=192.168.2.1/24

**NOTE:** для wlan0 нужно отключить механизм WPA-авторизации для создания 
Wireless Access Point: nohook wpa_supplicant

#### Перезагрузка и проверка состояния службы dhcp:
- sudo reboot
- sudo systemctl status dhcpcd.service

### 4. Настройка роутинга (packet forwarder)

Эта настройка позволяет задать правила для входящего / исходайего трафика, а 
также задать политику безопасности для роутера.

#### Для этого нужно создать скрипт:
- sudo vim /usr/local/sbin/systemd-iptables.sh

**NOTE:** скрипт приведен в файле iptables-template.sh

#### Скрипт необходимо сделать исполняемым:
- sudo chmod +x /usr/local/sbin/systemd-iptables.sh

#### Запуск скрипта вручную:
- sudo /usr/local/sbin/systemd-iptables.sh start
- sudo /usr/local/sbin/systemd-iptables.sh stop
- sudo /usr/local/sbin/systemd-iptables.sh restart

#### Создадим юнит для systemd для запуска скрипта при старте ОС:

[Unit]

Description=IPTables rules

After=network.target

[Service]

Type=oneshot

ExecStart=/usr/local/sbin/systemd-iptables.sh start

ExecStop=/usr/local/sbin/systemd-iptables.sh stop

ExecReload=/usr/local/sbin/systemd-iptables.sh restart

RemainAfterExit=yes

[Install]

WantedBy=multi-user.target

#### Разрешить использование юнита:
- sudo systemctl enable iptables.service

#### Перезапуск сервиса:
- sudo systemctl start iptables.service
- sudo systemctl status iptables.service

### 5. Беспроводная точка доступа

- iw list - информация о беспроводных интерфейсах
**NOTE:** В списке должно быть AP (access point).

#### Для настройки нужно следующее:
- sudo vim /etc/hostapd/hostapd.conf

	interface=wlan0

	driver=nl80211

	ssid=<network-name>

	hw_mode=g

	channel=6n

	ieee80211n=1

	wmm_enabled=1

	ht_capab=[HT40][SHORT-GI-20][DSSS_CCK-40]

	macaddr_acl=0

	auth_algs=1

	ignore_broadcast_ssid=0

	wpa=2

	wpa_key_mgmt=WPA-PSK

	wpa_passphrase=<password>

	rsn_pairwise=CCMP

	wps_state=0

#### Указать путь к конфиг файлу:
    sudo nano /etc/default/hostapd

	DAEMON_CONF="/etc/hostapd/hostapd.conf"

#### Перезагрузка и проверка статуса:
- sudo systemctl restart hostapd
- sudo systemctl status hostapd

**NOTE:** возможно понадобится сделать так:
- sudo systemctl unmask hostapd
- sudo systemctl enable hostapd
- sudo systemctl start hostapd
- sudo systemctl status hostapd

### 6. Настройка DHCP

Определим пул IP адресов для подключаемых устройств.
**Example:** wlan0: 192.168.2.10 - 192.168.2.100

#### Для настройки нужно:
- sudo vim /etc/dhcp/dhcpd.conf
- раскоментировать authoritative;
- в конец файла добавить:

		subnet 192.168.2.0 netmask 255.255.255.0

		{
 			range 192.168.2.10 192.168.2.100;

 			option broadcast-address 192.168.2.255;

 			option routers 192.168.2.1;

 			default-lease-time 600; 

 			max-lease-time 7200;

 			option domain-name "local-network";

 			# OpenDNS

 			option domain-name-servers 208.67.222.222, 208.67.220.220;
		}

#### Проверка синтаксиса:
- sudo dhcpd -t

#### Разрешим работу dhcp на интерфейсе (имена интерфейсов ч/з пробел):
- sudo vim /etc/default/isc-dhcp-server

	INTERFACESv4="eth0 wlan0"

	INTERFACESv6=""

#### Перезапуск и проверка статуса:
- sudo systemctl start isc-dhcp-server
- sudo systemctl status isc-dhcp-server

### 7 Reference:

[origin](https://ph0en1x.net/105-raspberry-pi-handmade-server-router-software.html#raspberry-pi-start-config)
