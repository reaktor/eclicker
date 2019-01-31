var express = require('express');
var fs = require('fs');
var router = express.Router();
const fileName = '/Users/mkorostoff/Arduino/config.json';

router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

router.get('/form_get', function(req, res, next) {
  let file = fs.readFileSync(fileName, "utf8");
  res.send(file);
});

router.post('/form_submit', function(req, res, next) {
  fs.writeFileSync(fileName, JSON.stringify(req.body))
  res.send('1');
});

module.exports = router;
