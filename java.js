//Khởi tạo và kết nối Firebase---------------------------------//
const firebaseConfig = {
    apiKey: "AIzaSyBOZV8pasqrVEFgZp-mHD6V4l0IHleUPko",
    authDomain: "dht-nhietdo-doam.firebaseapp.com",
    databaseURL: "https://dht-nhietdo-doam-default-rtdb.firebaseio.com",
    projectId: "dht-nhietdo-doam",
    storageBucket: "dht-nhietdo-doam.appspot.com",
    messagingSenderId: "939898012489",
    appId: "1:939898012489:web:a30e98b5b45c8e6d44d098",
    measurementId: "G-DT6FED92X9"
  };
function dongho() {
    var time = new Date();
    var gio = time.getHours();
    var phut = time.getMinutes();
    var giay = time.getSeconds();
    if (gio < 10) 
        gio = "0" + gio;
    if (phut < 10) 
        phut = "0" + phut;
    if (giay < 10) 
        giay = "0" + giay;
    document.getElementById("time").innerHTML = gio + ":" + phut + ":" + giay;
    setTimeout(dongho, 1000);
}
//Tạo hàm-------------------------------------------------------//
function function_NA(){
    nd_NA.on('value', snap => ndNA.innerText = snap.val());
    da_NA.on('value', snap => daNA.innerText = snap.val());
    lm_NA.on('value', snap => lmNA.innerText = snap.val());
}
function function_HN(){
    nd_HN.on('value', snap => ndHN.innerText = snap.val());
    da_HN.on('value', snap => daHN.innerText = snap.val());
    lm_HN.on('value', snap => lmHN.innerText = snap.val());
}
function function_CM(){
    nd_CM.on('value', snap => ndCM.innerText = snap.val());
    da_CM.on('value', snap => daCM.innerText = snap.val());
    lm_CM.on('value', snap => lmCM.innerText = snap.val());
}
function function_HL(){
    nd_HL.on('value', snap => ndHL.innerText = snap.val());
    da_HL.on('value', snap => daHL.innerText = snap.val());
    lm_HL.on('value', snap => lmHL.innerText = snap.val());
}
//Hàm điều khiển hotline--------------------------------------------//
function hotlinecontrol() {
    let bton = document.querySelector('#bton');
    let btoff = document.querySelector('#btoff');
    let img1 = document.querySelector('#call');
    bton.addEventListener('click', () => {
      img1.src = 'image/call_on.gif';
      firebase.database().ref("hotline").set({dienthoai: 1})
    });
    btoff.addEventListener('click', () => {
      img1.src = 'image/call_off.png';
      firebase.database().ref("hotline").set({dienthoai: 0})
    });
  }
//Hàm Booking--------------------------------------------//
function booking() {
    let btn1 = document.querySelector('#btn1');
    let img2 = document.querySelector('#book');
    var img = false
    btn1.addEventListener('click', () => {
        img = !img;

        if(img){
        img2.src = 'image/booking_sucess.png'; 
        firebase.database().ref("booking").set({book:1})
        }

        else{
        img2.src = 'image/booking.png';
        firebase.database().ref("booking").set({book:0})
        }
    });
  }
//Hàm Cost--------------------------------------------//
function getvalueslider() {
    var slider = document.getElementById("myRange");
    var output = document.getElementById("sliderValue");
    output.textContent = slider.value; 
    slider.addEventListener("input", function() {
        output.textContent = this.value; 
    });

    slider.addEventListener('input', function() {
        var value = parseInt(slider.value);
        sliderValue.textContent = value;
        firebase.database().ref('Gia tien').set(value);  
    })
}