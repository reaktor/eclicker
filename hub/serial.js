const BOOTUP = "1";
const RESET = "2";
var fs = require('fs');
const fileName = '/Users/mkorostoff/Arduino/config.json';

const SerialPort = require('serialport');
const port = new SerialPort('/dev/cu.usbmodem14201', {
  baudRate: 9600
});

port.on('data', function (data) {
  let datum = data.toString().trim();
  console.log(datum)
  switch (datum) {
    case 'a':
      break;
    case 'b':
      break;
    case 'c':
      break;
    case 'd':
      break;
    case RESET:
      port.write(getConfig());
      break;
    case BOOTUP:
      port.write(getConfig());
      break;
    default:
      break;
  }
  function getConfig() {
    let conf = fs.readFileSync(fileName, "utf8");
    return JSON.parse(conf).labels.join('|');
  }
})