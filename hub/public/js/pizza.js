/**
 * This file is just fucking horrible, nothing about it is good at all.
 * It's literally something I threw together in 40 minutes to demo a
 * broader architctural concept, so don't judge it, this is really
 * not the point of this project.
 */
fetch('/pizza/reset');
var delivery1 = 0;
var delivery2 = 0;
var delivery3 = 0;
var delayProcessed = 0;
var interval1;
var interval2;
var interval3;

setInterval(function(){
  fetch('/pizza/read').then(function(res){
    return res.json();
  }).then(function(jason){
    if (jason.b === 1 && !delivery1) {
      delivery1 = 1;
      clearInterval(interval2);
      delivered("delivered1")
      hide("time1")
      countDown(17, "time2");
      green("time2");
      yellow("time3");
      moveDriver(195, 360);
    }
    if (jason.b === 2 && !delivery2) {
      delivery2 = 1;
      clearInterval(interval3);
      delivered("delivered2")
      hide("time2")
      interval3 = countDown(5, "time3");
      green("time3");
      moveDriver(55, 760);
    }
    if (jason.b === 3 && !delivery3) {
      delivery3 = 1;
      delivered("delivered3")
      hide("time3")
      moveDriver(400, 1150);
    }
    if (jason.d === 1 && !delayProcessed) {
      delayProcessed = 1;
      yellow("time3")
      clearInterval(interval3);
      interval3 = countDown(14, "time3")
    }
  });
}, 300);

interval1 = countDown(18, "time1");
interval2 = countDown(27, "time2");
interval3 = countDown(40, "time3");

function moveDriver(x, y) {
  document.getElementById('driver').style = "top: " + x + "px; left: " + y + "px;";
}
function green(element) {
  document.getElementById(element).style = 'color: green';
}
function yellow(element) {
  document.getElementById(element).style = 'color: orange';
}
function delivered(element) {
  document.getElementById(element).innerHTML = 'DELIVERED';
}
function hide(element) {
  document.getElementById(element).style = 'display:none;';
}
function countDown(minutes, element) {
  var countDownDate = new Date(new Date().getTime() + minutes*60000);
  return setInterval(function() {
    var now = new Date().getTime();
    var distance = countDownDate - now;
    var minutes = Math.floor((distance % (1000 * 60 * 60)) / (1000 * 60));
    var seconds = Math.floor((distance % (1000 * 60)) / 1000);
    document.getElementById(element).innerHTML = minutes + "m " + seconds + "s ";
  }, 1000);
}