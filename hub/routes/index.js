var express = require('express');
var fs = require('fs');
var router = express.Router();
const configFile = '/Users/mkorostoff/Arduino/config.json';
const pizzaDataBase = '/Users/mkorostoff/Arduino/pizza.json';
const RESET = 2;

router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

router.get('/form_get', function(req, res, next) {
  let file = fs.readFileSync(configFile, "utf8");
  res.send(file);
});


router.post('/form_submit', function(req, res, next) {
  fs.writeFileSync(configFile, JSON.stringify(req.body))
  res.send('1');
});

router.get('/pizza/reset', function(req, res, next) {
  fs.writeFileSync(pizzaDataBase, JSON.stringify({a: 0, b: 0, c: 0, d: 0}))
  res.send('1');
});

router.post('/pizza/write', function(req, res, next) {
  let file = fs.readFileSync(pizzaDataBase, "utf8");
  file = JSON.parse(file);
  file[req.body[0]]++;
  fs.writeFileSync(pizzaDataBase, JSON.stringify(file))
});

router.get('/pizza/read', function(req, res, next) {
  let file = fs.readFileSync(pizzaDataBase, "utf8");
  file = JSON.parse(file);
  res.json(file);
});

router.get('/pizza/view', function(req, res, next) {
  res.render('pizza');
});

module.exports = router;
