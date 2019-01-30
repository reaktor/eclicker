const BOOTUP = "1";
const RESET = "2";

const SerialPort = require('serialport');
const port = new SerialPort('/dev/cu.usbmodem14201', {
  baudRate: 9600
});

port.on('data', function (data) {
  let datum = data.toString().trim();
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
      port.write('Update|From|The|Cloud');
      break;
    case BOOTUP:
      port.write('Download|From|The|Cloud');
      break;
    default:
      break;
  }
})