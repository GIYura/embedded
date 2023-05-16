#### HOW-TO start

**NOTE:** The PCF8583 is a clock and calendar chip. 

##### Connection

PCF pin ---------- Raspberry pin

VDD                 3.3V
GNG                 GND
SCL                 SCL1
SDA                 SDA1

##### Driver

- Enter driver dir;
- Run make to build pcf driver;

```
make
```
- Load **.ko** file
```
make load
```

##### Test

- Enter test dir;
- Run gcc to build executable
```
gcc test.c -o test
```
- Run executable
```
sudo ./test /dev/pcf8583
```

