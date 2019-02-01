const BOOTUP = "1";
const RESET = "2";
const fetch = require("node-fetch");
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
    case 'b':
    case 'c':
    case 'd':
      fetch(getCallbackUrl(), {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify([datum]),
      });
      break;
    case RESET:
      port.write(getLabels());
      break;
    case BOOTUP:
      port.write(getLabels());
      break;
    default:
      break;
  }
  function getLabels() {
    return getConf().labels.join('|');
  }
  function getCallbackUrl() {
    return getConf().url;
  }
  function getConf() {
    let conf = fs.readFileSync(fileName, "utf8");
    return JSON.parse(conf);
  }
})