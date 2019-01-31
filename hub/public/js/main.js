fetch('/form_get')
  .then(function(response) {
    return response.json();
  })
  .then(function(jason) {
    document.getElementById('button1').value = jason.labels[0];
    document.getElementById('button2').value = jason.labels[1];
    document.getElementById('button3').value = jason.labels[2];
    document.getElementById('button4').value = jason.labels[3];
    document.getElementById('url').value = jason.url;
  });

document.getElementById('submit').addEventListener('click', function(e) {
  e.preventDefault();
  var payload = {
    labels: [
      document.getElementById('button1').value,
      document.getElementById('button2').value,
      document.getElementById('button3').value,
      document.getElementById('button4').value,
    ],
    url: document.getElementById('url').value
  }
  fetch('form_submit', {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify(payload),
  })
  .then(function(response) {
    var alrt = document.getElementById('alert');
    alrt.classList.add('visible');
    setTimeout(function(){
      alrt.classList.remove('visible');
    }, 2000);
  });
})