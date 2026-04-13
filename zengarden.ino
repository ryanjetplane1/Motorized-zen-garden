#include <WiFi.h>
#include <WebServer.h>
#include <math.h>

const int S_PINS[] = {0, 1, 2, 3}; 
const int E_PINS[] = {4, 5, 6, 7}; 
const int STBY = 8;

WebServer server(80);

float L1 = 32.0, L2 = 32.0;
int curS = 0, curE = 0;

// FIXED: Added [4][4] to define the 2D array
const int seq[4][4] = {
  {1,0,0,1},
  {1,0,1,0},
  {0,1,1,0},
  {0,1,0,1}
};

void step(int m, int dir) {
  static int sI = 0, eI = 0;
  int &idx = (m == 0) ? sI : eI;
  const int* p = (m == 0) ? S_PINS : E_PINS;
  idx = (idx + dir + 4) % 4;
  for(int j=0; j<4; j++) digitalWrite(p[j], seq[idx][j]);
  delay(10); 
}

void resetArm() {
  digitalWrite(STBY, HIGH);
  while(curE != 0) { int d = (0 > curE) ? 1 : -1; step(1, d); curE += d; }
  while(curS != 0) { int d = (0 > curS) ? 1 : -1; step(0, d); curS += d; }
  digitalWrite(STBY, LOW);
}

void moveArm(float x, float y) {
  float d2 = x*x + y*y;
  float d = sqrt(d2);
  if (d > 64 || d < 0.1) return;
  float t2 = acos((d2 - 2048.0) / 2048.0);
  float t1 = atan2(y, x) - atan2(32.0 * sin(t2), 32.0 + 32.0 * cos(t2));
  int tarS = t1 * 326; 
  int tarE = t2 * 326;
  if (tarS > 1900 || tarS < -1900) resetArm();
  digitalWrite(STBY, HIGH);
  while(curS != tarS) { int d = (tarS > curS) ? 1 : -1; step(0, d); curS += d; }
  while(curE != tarE) { int d = (tarE > curE) ? 1 : -1; step(1, d); curE += d; }
  digitalWrite(STBY, LOW);
}

const char HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html><head><meta name="viewport" content="width=device-width, initial-scale=1">
<style>
  :root { --accent: #ffffff; --bg: #111; --card: #1c1c1e; }
  body { background: var(--bg); color: #fff; font-family: -apple-system, system-ui, sans-serif; margin: 0; display: flex; flex-direction: column; align-items: center; justify-content: center; min-height: 100vh; }
  .container { width: 340px; background: var(--card); padding: 25px; border-radius: 32px; box-shadow: 0 30px 60px rgba(0,0,0,0.8); border: 1px solid #2c2c2e; text-align: center; }
  .status { font-size: 11px; font-weight: 700; color: #888; text-transform: uppercase; letter-spacing: 2px; margin-bottom: 5px; }
  .mode-name { font-size: 20px; font-weight: 600; margin-bottom: 25px; color: var(--accent); }
  canvas { background: #000; border-radius: 50%; width: 280px; height: 280px; touch-action: none; cursor: crosshair; border: 4px solid #2c2c2e; margin-bottom: 30px; }
  .btn-grid { display: grid; grid-template-columns: 1fr 1fr; gap: 12px; }
  button { background: #2c2c2e; border: none; color: #fff; padding: 16px; border-radius: 16px; font-size: 13px; font-weight: 600; transition: 0.3s; }
  button:active { transform: scale(0.95); background: #3a3a3c; }
  button.active { background: #fff; color: #000; }
  .btn-main { grid-column: span 2; background: #fff; color: #000; font-size: 15px; margin-top: 8px; }
  .btn-clear { grid-column: span 2; background: transparent; color: #ff3b30; font-size: 12px; margin-top: 5px; }
</style></head>
<body>
  <div class="container">
    <div class="status" id="st-top">SYSTEM READY</div>
    <div class="mode-name" id="mode-txt">Idle</div>
    <canvas id="c" width="300" height="300"></canvas>
    <div class="btn-grid">
      <button id="B-SPIRAL" onclick="setM('SPIRAL')">SPIRAL</button>
      <button id="B-STAR" onclick="setM('STAR')">STAR</button>
      <button id="B-HEX" onclick="setM('HEX')">HEXAGON</button>
      <button id="B-DRAW" onclick="setM('DRAW')">FREE DRAW</button>
      <button class="btn-main" onclick="run()">START SEQUENCE</button>
      <button class="btn-clear" onclick="clr()">Clear All</button>
    </div>
  </div>
<script>
  var c=document.getElementById('c'), ctx=c.getContext('2d'), active=false, pts=[], mode='IDLE';
  function setM(m){ mode=m; document.getElementById('mode-txt').innerText=m; document.querySelectorAll('button').forEach(b=>b.classList.remove('active')); if(m!='IDLE')document.getElementById('B-'+m).classList.add('active'); }
  function clr(){ ctx.clearRect(0,0,300,300); pts=[]; setM('IDLE'); document.getElementById('st-top').innerText='SYSTEM READY'; }
  function getXY(e){ var r=c.getBoundingClientRect(), ev=e.touches?e.touches:e; return {x:(ev.clientX-r.left-150)/2.3, y:(150-(ev.clientY-r.top))/2.3, px:ev.clientX-r.left, py:ev.clientY-r.top}; }
  c.onmousedown=c.ontouchstart=(e)=>{ if(mode!='DRAW')clr(); setM('DRAW'); active=true; };
  window.onmouseup=window.ontouchend=()=>{ active=false; };
  c.onmousemove=c.ontouchmove=(e)=>{ if(!active)return; var p=getXY(e); pts.push(p); ctx.fillStyle="#fff"; ctx.beginPath(); ctx.arc(p.px,p.py,2,0,7); ctx.fill(); };
  async function run(){
    document.getElementById('st-top').innerText='RUNNING...';
    if(mode=='DRAW'){ for(var p of pts){ await fetch('/d?x='+p.x.toFixed(1)+'&y='+p.y.toFixed(1)); } }
    else{ await fetch('/p?s='+mode); }
    document.getElementById('st-top').innerText='COMPLETE';
  }
</script></body></html>)rawliteral";

void setup() {
  for(int i=0; i<9; i++) pinMode(i, OUTPUT);
  WiFi.softAP("ZenGarden", "zen12345");
  server.on("/", []() { server.send(200, "text/html", HTML); });
  server.on("/d", []() { moveArm(server.arg("x").toFloat(), server.arg("y").toFloat()); server.send(200); });
  server.on("/p", []() {
    String s = server.arg("s"); resetArm();
    if(s=="SPIRAL"){ for(float i=0;i<64;i+=1.5){ float a=i*0.5; moveArm(i*cos(a),i*sin(a)); } }
    else if(s=="STAR"){ for(int i=0;i<6;i++){ float a=i*2.5; moveArm(60*cos(a),60*sin(a)); a+=1.25; moveArm(20*cos(a),20*sin(a)); } }
    else if(s=="HEX"){ for(int i=0;i<=6;i++){ float a=i*1.047; moveArm(50*cos(a),50*sin(a)); } }
    server.send(200);
  });
  server.begin();
}

void loop() { server.handleClient(); }
