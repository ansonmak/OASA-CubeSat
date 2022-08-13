static const char PROGMEM INDEX_HTML[] = R"rawliteral(
<!doctype html>
<html>
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width,initial-scale=1">
        <title>CubeSat Control Panel</title>
        <style>
            body {
                font-family: Arial, Helvetica, sans-serif;
                background: #181818;
                color: #efefef;
                font-size: 16px;
            }
            h2 {
                font-size: 18px;
            }
            section.main {
                display: flex;
            }
            #menu,
            section.main {
                flex-direction: column;
            }
            #menu {
                display: none;
                flex-wrap: nowrap;
                min-width: 340px;
                background: #363636;
                padding: 8px;
                border-radius: 4px;
                margin-top: -10px;
                margin-right: 10px;
            }
            #content {
                display: flex;
                flex-wrap: wrap;
                align-items: stretch;
            }
            figure {
                padding: 0;
                margin: 0;
                -webkit-margin-before: 0;
                margin-block-start: 0;
                -webkit-margin-after: 0;
                margin-block-end: 0;
                -webkit-margin-start: 0;
                margin-inline-start: 0;
                -webkit-margin-end: 0;
                margin-inline-end: 0;
            }
            figure img {
                display: block;
                width: 100%;
                height: auto;
                border-radius: 4px;
                margin-top: 8px;
            }
            @media (min-width: 800px) and (orientation: landscape) {
                #content {
                    display: flex;
                    flex-wrap: nowrap;
                    align-items: stretch;
                }
                figure img {
                    display: block;
                    max-width: 100%;
                    max-height: calc(100vh - 40px);
                    width: auto;
                    height: auto;
                }
                figure {
                    padding: 0;
                    margin: 0;
                    -webkit-margin-before: 0;
                    margin-block-start: 0;
                    -webkit-margin-after: 0;
                    margin-block-end: 0;
                    -webkit-margin-start: 0;
                    margin-inline-start: 0;
                    -webkit-margin-end: 0;
                    margin-inline-end: 0;
                }
            }
            section #buttons {
                display: flex;
                flex-wrap: nowrap;
                justify-content: space-between;
            }
            #nav-toggle {
                cursor: pointer;
                display: block;
            }
            #nav-toggle-cb {
                outline: 0;
                opacity: 0;
                width: 0;
                height: 0;
            }
            #nav-toggle-cb:checked + #menu {
                display: flex;
            }
            .input-group {
                display: flex;
                flex-wrap: nowrap;
                line-height: 22px;
                margin: 5px 0;
            }
            .input-group > label {
                display: inline-block;
                padding-right: 10px;
                min-width: 47%;
            }
            .input-group input,
            .input-group select {
                flex-grow: 1;
            }
            .range-max,
            .range-min {
                display: inline-block;
                padding: 0 5px;
            }
            button {
                display: block;
                margin: 5px;
                padding: 5px 12px;
                border: 0;
                line-height: 28px;
                cursor: pointer;
                color: #fff;
                background: #035806;
                border-radius: 5px;
                font-size: 16px;
                outline: 0;
                width: 100px;  
            }
            .button2 {background-color: #008CBA; width: 100px;} /* Blue */
            .button3 {background-color: #f44336; width: 100px;} /* Red */ 
            .button4 {background-color: #e7e7e7; color: black; width: 120px;} /* Gray */ 
            .button5 {background-color: #555555; width: 100px;} /* Black */
            .button6 {visibility: hidden; width: 100px;} /* Black */
            .button7 {width: 130px;} /* Black */
            button:hover {
                background: #ff494d;
            }
            button:active {
                background: #f21c21;
            }
            button.disabled {
                cursor: default;
                background: #a0a0a0;
            }
            input[type="range"] {
                -webkit-appearance: none;
                width: 100%;
                height: 22px;
                background: #363636;
                cursor: pointer;
                margin: 0;
            }
            input[type="range"]:focus {
                outline: 0;
            }
            input[type="range"]::-webkit-slider-runnable-track {
                width: 100%;
                height: 2px;
                cursor: pointer;
                background: #efefef;
                border-radius: 0;
                border: 0 solid #efefef;
            }
            input[type="range"]::-webkit-slider-thumb {
                border: 1px solid rgba(0, 0, 30, 0);
                height: 22px;
                width: 22px;
                border-radius: 50px;
                background: #ff3034;
                cursor: pointer;
                -webkit-appearance: none;
                margin-top: -11.5px;
            }
            input[type="range"]:focus::-webkit-slider-runnable-track {
                background: #efefef;
            }
            input[type="range"]::-moz-range-track {
                width: 100%;
                height: 2px;
                cursor: pointer;
                background: #efefef;
                border-radius: 0;
                border: 0 solid #efefef;
            }
            input[type="range"]::-moz-range-thumb {
                border: 1px solid rgba(0, 0, 30, 0);
                height: 22px;
                width: 22px;
                border-radius: 50px;
                background: #ff3034;
                cursor: pointer;
            }
            input[type="range"]::-ms-track {
                width: 100%;
                height: 2px;
                cursor: pointer;
                background: 0 0;
                border-color: transparent;
                color: transparent;
            }
            input[type="range"]::-ms-fill-lower {
                background: #efefef;
                border: 0 solid #efefef;
                border-radius: 0;
            }
            input[type="range"]::-ms-fill-upper {
                background: #efefef;
                border: 0 solid #efefef;
                border-radius: 0;
            }
            input[type="range"]::-ms-thumb {
                border: 1px solid rgba(0, 0, 30, 0);
                height: 22px;
                width: 22px;
                border-radius: 50px;
                background: #ff3034;
                cursor: pointer;
                height: 2px;
            }
            input[type="range"]:focus::-ms-fill-lower {
                background: #efefef;
            }
            input[type="range"]:focus::-ms-fill-upper {
                background: #363636;
            }
            .switch {
                display: block;
                position: relative;
                line-height: 22px;
                font-size: 16px;
                height: 22px;
            }
            .switch input {
                outline: 0;
                opacity: 0;
                width: 0;
                height: 0;
            }
            .slider {
                width: 50px;
                height: 22px;
                border-radius: 22px;
                cursor: pointer;
                background-color: grey;
            }
            .slider,
            .slider:before {
                display: inline-block;
                transition: 0.4s;
            }
            .slider:before {
                position: relative;
                content: "";
                border-radius: 50%;
                height: 16px;
                width: 16px;
                left: 4px;
                top: 3px;
                background-color: #fff;
            }
            input:checked + .slider {
                background-color: #ff3034;
            }
            input:checked + .slider:before {
                -webkit-transform: translateX(26px);
                transform: translateX(26px);
            }
            select {
                border: 1px solid #363636;
                font-size: 14px;
                height: 22px;
                outline: 0;
                border-radius: 5px;
            }
            .image-container {
                position: absolute;
                top: 10px;
                left: 55%;
                /* margin-right: -50%;
                transform: translate(-50%, -50%);
                min-width: 160px; */
            }
            .control-container {
                position: relative;
                top: 100px;
                left: 15%;
                /* margin-right: -50%;
                transform: translate(-50%, -50%); */
            }
            .slider-container {
                position: relative;
                top: 200px;
                right: 50%;
                width: 400px;
                /* margin-left: -50%;
                transform: translate(-50%, -50%); */
            }
            .close {
                position: absolute;
                right: 5px;
                top: 13px;
                background: #ff3034;
                width: 16px;
                height: 16px;
                border-radius: 100px;
                color: #fff;
                text-align: center;
                line-height: 18px;
                cursor: pointer;
            }
            .hidden {
                display: none;
            }
            .rotate90 {
                -webkit-transform: rotate(270deg);
                -moz-transform: rotate(270deg);
                -o-transform: rotate(270deg);
                -ms-transform: rotate(270deg);
                transform: rotate(270deg);
            }
            .sensor-container {
                position: relative;
                top: 30px;
                left: 20%;
                width: 200px;
                color: "#0000AA";
            }
            .meter{
                font-size: 24px;
                position: relative;
                padding-left: 5px;
                padding-top: 5px;
                height:   25px;
                width: 150px;
                border-radius: 5px;
                color: #FFFFFF;
                line-height: 20px;
                transition: all 200ms ease-in-out;
                background-color: #00AA00;
                white-space: nowrap;
            }
        </style>
    </head>
    <body onload="reloadData()">
        <section class="main">
            <figure>
                <div id="stream-container" class="image-container">
                <div class="close" id="close-stream">×</div>
                <img id="stream" src=""> <!-- class="rotate90"> -->
                </div>
            </figure>    

            <div id='sensor', class='sensor-container'>
                Battery Percentage:
                <br>
                <div class="meter" id = "bat"></div>
                <br>
                Light sensor 1:
                <br>
                <div class="meter" id = "light1"></div>
                <br>
                Light sensor 2:
                <br>
                <div class="meter" id = "light2"></div>
            </div>

            <section id="buttons">
                <div id="controls" class="control-container">
                  <table>
                  <tr><td align="center"><button class="button button6" id="get-still">Image</button></td><td align="center"><button class="button button7" id="toggle-stream">Start Stream</button></td><td align="center"><button class="button button4" id="deploy" onclick="fetch(document.location.origin+'/control?var=deploy&val=0');">Deploy</button></td></tr>
                  </table>
                </div>
                <div id="sliders" class="slider-container">
                  Motor Speed: <output id="motor_spd">0</output>%
                  <br>
                  <input type="range" id="speed" min="-100" max="100" value="0" oninput="try{fetch(document.location.origin+'/control?var=speed&val='+this.value);motor_spd.value = this.value;}catch(e){}">
                  <br>
                  LED Brightness: <output id="led_bright">0</output>%
                  <br>
                  <input type="range" id="led" min="0" max="100" value="0" oninput="try{fetch(document.location.origin+'/control?var=led&val='+this.value);led_bright.value = this.value;}catch(e){}">
                  <br>
                  Video Size:
                  <br>
                  <input type="range" id="framesize" min="3" max="7" value="3" oninput="try{fetch(document.location.origin+'/control?var=framesize&val='+this.value);}catch(e){}">
                  <br>
                  Video Quality: 
                  <br>
                  <input type="range" id="quality" min="10" max="63" value="10" oninput="try{fetch(document.location.origin+'/control?var=quality&val='+this.value);}catch(e){}">
                </div>
            </section>         
        </section>
        <script>
            function reloadData() {
                fetch(`${document.location.origin}/status`)//, {headers : { 'Content-Type': 'application/json','Accept': 'application/json'}})
                .then(response => response.json())
                .then(data => {
                    // battery voltage
                    vol = data.bat_vol
                    perc = data.bat_percent
                    document.getElementById("bat").style.width=(perc+"%")
                    document.getElementById("bat").innerHTML= perc + "%(" + vol + "V)"
                    max_col_val = 170;
                    red = (100 - perc)/100 * max_col_val;
                    green = perc/100 * max_col_val;
                    color = "rgb("+red+","+green+",0)";
                    document.getElementById("bat").style.backgroundColor=color
                    // light sensor1
                    light1 = data.light1
                    document.getElementById("light1").style.width=(light1+"%")
                    document.getElementById("light1").innerHTML=light1
                    max_col_val = 170;
                    red = (255 - light1)/255*max_col_val;
                    green = light1/255*max_col_val;
                    color = "rgb("+red+","+green+",0)";
                    document.getElementById("light1").style.backgroundColor=color
                    // light sensor2
                    light2 = data.light2
                    document.getElementById("light2").style.width=(light2+"%")
                    document.getElementById("light2").innerHTML=light2
                    max_col_val = 170;
                    red = (255 - light2)/255*max_col_val;
                    green = light2/255*max_col_val;
                    color = "rgb("+red+","+green+",0)";
                    document.getElementById("light2").style.backgroundColor=color
                })
                setTimeout(reloadData,50);
            }

            document.addEventListener('DOMContentLoaded', function (event) {
                var baseHost = document.location.origin // ip address of web server
                var streamUrl = baseHost + ':81'
            
                const hide = el => {
                el.classList.add('hidden')
                }
                const show = el => {
                el.classList.remove('hidden')
                }
            
                const disable = el => {
                el.classList.add('disabled')
                el.disabled = true
                }
            
                const enable = el => {
                el.classList.remove('disabled')
                el.disabled = false
                }
            
                const updateValue = (el, value, updateRemote) => {
                updateRemote = updateRemote == null ? true : updateRemote
                let initialValue
                if (el.type === 'checkbox') {
                    initialValue = el.checked
                    value = !!value
                    el.checked = value
                } else {
                    initialValue = el.value
                    el.value = value
                }
            
                if (updateRemote && initialValue !== value) {
                    updateConfig(el);
                } else if(!updateRemote){
                    if(el.id === "aec"){
                    value ? hide(exposure) : show(exposure)
                    } else if(el.id === "agc"){
                    if (value) {
                        show(gainCeiling)
                        hide(agcGain)
                    } else {
                        hide(gainCeiling)
                        show(agcGain)
                    }
                    } else if(el.id === "awb_gain"){
                    value ? show(wb) : hide(wb)
                    } else if(el.id === "face_recognize"){
                    value ? enable(enrollButton) : disable(enrollButton)
                    }
                }
                }
            
                function updateConfig (el) {
                let value
                switch (el.type) {
                    case 'checkbox':
                    value = el.checked ? 1 : 0
                    break
                    case 'range':
                    case 'select-one':
                    value = el.value
                    break
                    case 'button':
                    case 'submit':
                    value = '1'
                    break
                    default:
                    return
                }
            
                const query = `${baseHost}/control?var=${el.id}&val=${value}`
            
                fetch(query)
                    .then(response => {
                    console.log(`request to ${query} finished, status: ${response.status}`)
                    })
                }
            
                document
                .querySelectorAll('.close')
                .forEach(el => {
                    el.onclick = () => {
                    hide(el.parentNode)
                    }
                })
            
                // read initial values
                fetch(`${baseHost}/status`)
                .then(function (response) {
                    return response.json()
                })
                .then(function (state) {
                    document
                    .querySelectorAll('.default-action')
                    .forEach(el => {
                        updateValue(el, state[el.id], false)
                    })
                })
            
                const view = document.getElementById('stream')
                const viewContainer = document.getElementById('stream-container')
                const stillButton = document.getElementById('get-still')
                const streamButton = document.getElementById('toggle-stream')
                const enrollButton = document.getElementById('face_enroll')
                const closeButton = document.getElementById('close-stream')
            
                const stopStream = () => {
                window.stop();
                streamButton.innerHTML = 'Start Stream'
                }
            
                const startStream = () => {
                view.src = `${streamUrl}/stream`
                show(viewContainer)
                streamButton.innerHTML = 'Stop Stream'
                }
            
                // Attach actions to buttons
                stillButton.onclick = () => {
                stopStream()
                view.src = `${baseHost}/capture?_cb=${Date.now()}`
                show(viewContainer)
                }
            
                closeButton.onclick = () => {
                stopStream()
                hide(viewContainer)
                }
            
                streamButton.onclick = () => {
                const streamEnabled = streamButton.innerHTML === 'Stop Stream'
                if (streamEnabled) {
                    stopStream()
                } else {
                    startStream()
                }
                }
            
                enrollButton.onclick = () => {
                updateConfig(enrollButton)
                }
            
                // Attach default on change action
                document
                .querySelectorAll('.default-action')
                .forEach(el => {
                    el.onchange = () => updateConfig(el)
                })
            
                // Custom actions
                // Gain
                const agc = document.getElementById('agc')
                const agcGain = document.getElementById('agc_gain-group')
                const gainCeiling = document.getElementById('gainceiling-group')
                agc.onchange = () => {
                updateConfig(agc)
                if (agc.checked) {
                    show(gainCeiling)
                    hide(agcGain)
                } else {
                    hide(gainCeiling)
                    show(agcGain)
                }
                }
            
                // Exposure
                const aec = document.getElementById('aec')
                const exposure = document.getElementById('aec_value-group')
                aec.onchange = () => {
                updateConfig(aec)
                aec.checked ? hide(exposure) : show(exposure)
                }
            
                // AWB
                const awb = document.getElementById('awb_gain')
                const wb = document.getElementById('wb_mode-group')
                awb.onchange = () => {
                updateConfig(awb)
                awb.checked ? show(wb) : hide(wb)
                }
            
                // Detection and framesize
                const detect = document.getElementById('face_detect')
                const recognize = document.getElementById('face_recognize')
                const framesize = document.getElementById('framesize')
            
                framesize.onchange = () => {
                updateConfig(framesize)
                if (framesize.value > 5) {
                    updateValue(detect, false)
                    updateValue(recognize, false)
                }
                }
            
                detect.onchange = () => {
                if (framesize.value > 5) {
                    alert("Please select CIF or lower resolution before enabling this feature!");
                    updateValue(detect, false)
                    return;
                }
                updateConfig(detect)
                if (!detect.checked) {
                    disable(enrollButton)
                    updateValue(recognize, false)
                }
                }
            
                recognize.onchange = () => {
                if (framesize.value > 5) {
                    alert("Please select CIF or lower resolution before enabling this feature!");
                    updateValue(recognize, false)
                    return;
                }
                updateConfig(recognize)
                if (recognize.checked) {
                    enable(enrollButton)
                    updateValue(detect, true)
                } else {
                    disable(enrollButton)
                }
                }
            });
        </script>
    </body>
</html>
)rawliteral";
