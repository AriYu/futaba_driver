# Futaba40x Driver

双葉のコマンド方式サーボをRSC-U485を使ってUbuntu14.04で動かす。

```bash
$ mkdir build & cd build
$ cmake ..
$ make
```

```bash
$ sudo modprobe ftdi-sio
$ sudo echo "1115 0008" > /sys/bus/usb-serial/drivers/ftdi_sio/new_id
$ sudo chmod +x /dev/ttyUSB0
```

### TODO
- 複数のサーボをコントロールできるようにする

### 参考
- http://futaba.co.jp/robot/download/sample_programs
- https://hirooka.pro/?p=6577
- https://taki4416.com/wordpress/2014/07/16/futaba%E3%81%AErsc-u485%E3%82%92ubutnu14-04%E3%81%A7%E4%BD%BF%E3%81%86/

---

*このプログラムは以下のプログラムを改変したものです。*
https://github.com/open-rdc/futaba_servo


## LICENSE
License-check is open source software under the BSD license.

