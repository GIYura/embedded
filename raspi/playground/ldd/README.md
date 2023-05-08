#### HOW-TO start

**NOTE:** модули ядра находятся по пути:
/lib/modules/'(uname -r)'. Заголовочный файлы ядра 
находятся /usr/src/linux-headers-'(uname -r)'

1. Установка kernel headers:

```
sudo apt install raspberrypi-kernel-headers
```
Проверить что в каталоге /usr/src/ есть headers:

```
ls /usr/src/
```

2. Проверить что версия ядра соответсвует версии модудей ядра:
```
uname -r
```
В каталоге /lib/modules/'(uname -r)' должна быть софт линк на 
/usr/src/linux-headers-'(uname -r)'

**NOTE:** после установки raspbian версия ядра 5.10.17-v7l+ (ядро kernel7.img), 
для загрузки другого ядра нужно в файле /boot/config.txt добавить строку kernel=kernel7vl.img

Выполнить перезагрузку.
После этого версия ядра и модулей будет соответствовать.

Video: [Source](https://www.youtube.com/playlist?list=PLCGpd0Do5-I3b5TtyqeF1UdyD4C-S-dMa)

Code: [Repo](https://github.com/Johannes4Linux/Linux_Driver_Tutorial)

Theory: [Reference](https://linux-kernel-labs.github.io/refs/heads/master/labs/device_drivers.html)

