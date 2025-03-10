var renderer = new THREE.WebGLRenderer({ antialias: true });
renderer.setSize(window.innerWidth, window.innerHeight);

if (window.innerWidth > 800) {
    renderer.shadowMap.enabled = true;
    renderer.shadowMap.type = THREE.PCFSoftShadowMap;
}
document.body.appendChild(renderer.domElement);

// Make it responsive
window.addEventListener("resize", onWindowResize, false);
function onWindowResize() {
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(window.innerWidth, window.innerHeight);
}

var camera = new THREE.PerspectiveCamera(20, window.innerWidth / window.innerHeight, 1, 500);
camera.position.set(0, 2, 14);

var scene = new THREE.Scene();
var city = new THREE.Object3D();
var smoke = new THREE.Object3D();
var town = new THREE.Object3D();
var createCarPos = true;
var uSpeed = 0.001;

// FOG background
var setcolor = 0xF02050;
scene.background = new THREE.Color(setcolor);
scene.fog = new THREE.Fog(setcolor, 10, 16);

// Random function
function mathRandom(num = 8) {
    return -Math.random() * num + Math.random() * num;
}

// Change building color
var setTinNum = true;
function setTintColor() {
    return setTinNum ? 0x000000 : 0xFFFFFF;
}

// Create the city
function init() {
    var segments = 2;
    for (var i = 1; i < 100; i++) {
        var geometry = new THREE.BoxGeometry(1, 1, 1, segments, segments, segments);
        var material = new THREE.MeshStandardMaterial({ color: setTintColor(), wireframe: false, side: THREE.DoubleSide });
        var cube = new THREE.Mesh(geometry, material);

        cube.castShadow = true;
        cube.receiveShadow = true;
        cube.rotationValue = 0.1 + Math.abs(mathRandom(8));
        cube.scale.y = 0.1 + Math.abs(mathRandom(8));

        var cubeWidth = 0.9;
        cube.scale.x = cube.scale.z = cubeWidth + mathRandom(1 - cubeWidth);
        cube.position.x = Math.round(mathRandom());
        cube.position.z = Math.round(mathRandom());

        town.add(cube);
    }

    // Particulars
    var gmaterial = new THREE.MeshToonMaterial({ color: 0xFFFF00, side: THREE.DoubleSide });
    var gparticular = new THREE.CircleGeometry(0.01, 3);
    var aparticular = 5;

    for (var h = 1; h < 300; h++) {
        var particular = new THREE.Mesh(gparticular, gmaterial);
        particular.position.set(mathRandom(aparticular), mathRandom(aparticular), mathRandom(aparticular));
        particular.rotation.set(mathRandom(), mathRandom(), mathRandom());
        smoke.add(particular);
    }

    var pmaterial = new THREE.MeshPhongMaterial({ color: 0x000000, side: THREE.DoubleSide, roughness: 10, metalness: 0.6, opacity: 0.9, transparent: true });
    var pgeometry = new THREE.PlaneGeometry(60, 60);
    var pelement = new THREE.Mesh(pgeometry, pmaterial);
    pelement.rotation.x = -90 * Math.PI / 180;
    pelement.position.y = -0.001;
    pelement.receiveShadow = true;
    city.add(pelement);
}

// Mouse function
var raycaster = new THREE.Raycaster();
var mouse = new THREE.Vector2(), INTERSECTED;
var intersected;

function onMouseMove(e) {
    e.preventDefault();
    mouse.x = (e.clientX / window.innerWidth) * 2 - 1;
    mouse.y = -(e.clientY / window.innerHeight) * 2 + 1;
}

function onDocumentTouchStart(e) {
    if (e.touches.length == 1) {
        e.preventDefault();
        mouse.x = e.touches[0].pageX - window.innerWidth / 2;
        mouse.y = e.touches[0].pageY - window.innerHeight / 2;
    }
}

function onDocumentTouchMove(e) {
    if (e.touches.length == 1) {
        e.preventDefault();
        mouse.x = e.touches[0].pageX - window.innerWidth / 2;
        mouse.y = e.touches[0].pageY - window.innerHeight / 2;
    }
}

window.addEventListener("mousemove", onMouseMove, false);
window.addEventListener("touchstart", onDocumentTouchStart, false);
window.addEventListener("touchmove", onDocumentTouchMove, false);

// Create lights
var ambientLight = new THREE.AmbientLight(0xFFFFFF, 4);
var lightFront = new THREE.SpotLight(0xFFFFFF, 20, 10);
var lightBack = new THREE.PointLight(0xFFFFFF, 0.5);
var SpotLightHelper = new THREE.SpotLightHelper(lightFront);

lightFront.rotation.x = 45 * Math.PI / 180;
lightFront.rotation.z = -45 * Math.PI / 180;
lightFront.position.set(5, 5, 5);
lightFront.castShadow = true;
lightFront.shadow.mapSize.width = 6000;
lightFront.shadow.mapSize.height = lightFront.shadow.mapSize.width;
lightFront.penumbra = 0.1;
lightBack.position.set(0, 6, 0);

smoke.position.y = 2;

scene.add(ambientLight);
city.add(lightFront);
scene.add(lightBack);
scene.add(city);
city.add(smoke);
city.add(town);

// Grid helper
var gridHelper = new THREE.GridHelper(60, 120, 0xFF0000, 0x000000);
city.add(gridHelper);

// Car world
var createCars = function (cScale = 2, cPos = 20, cColor = 0xFFFF00) {
    var cMat = new THREE.MeshToonMaterial({ color: cColor, side: THREE.DoubleSide });
    var cGeo = new THREE.BoxGeometry(1, cScale / 40, cScale / 40);
    var cElem = new THREE.Mesh(cGeo, cMat);
    var cAmp = 3;

    if (createCarPos) {
        createCarPos = false;
        cElem.position.x = -cPos;
        cElem.position.z = (mathRandom(cAmp));

        TweenMax.to(cElem.position, 3, { x: cPos, repeat: -1, yoyo: true, delay: mathRandom(3) });
    } else {
        createCarPos = true;
        cElem.position.x = (mathRandom(cAmp));
        cElem.position.z = -cPos;
        cElem.position.y = 90 * Math.PI / 180;

        TweenMax.to(cElem.position, 5, { z: cPos, repeat: -1, yoyo: true, delay: mathRandom(3), ease: Power1.easeInOut });
    }
    cElem.receiveShadow = true;
    cElem.castShadow = true;
    cElem.position.y = Math.abs(mathRandom(5));
    city.add(cElem);
}

var generateLines = function () {
    for (var i = 0; i < 60; i++) {
        createCars(0.1, 20);
    }
}

// Camera position
var cameraSet = function () {
    createCars(0.1, 20, 0xFFFFFF);
}

// Animate functions
var animate = function () {
    var time = Date.now() * 0.00005;
    requestAnimationFrame(animate);

    city.rotation.y -= ((mouse.x * 8) - camera.rotation.y) * uSpeed;
    city.rotation.x -= (-(mouse.y * 2) - camera.rotation.x) * uSpeed;
    if (city.rotation.x < -0.05) {
        city.rotation.x = -0.05;
    } else if (city.rotation.x > 1) {
        city.rotation.x = 1;
    }
    var cityRotation = Math.sin(Date.now() / 5000) * 13;
    for (let i = 0, l = town.children.length; i < l; i++) {
        var object = town.children[i];
    }

    smoke.rotation.y += 0.01;
    smoke.rotation.x += 0.01;

    camera.lookAt(city.position);
    renderer.render(scene, camera);
}

document.addEventListener("DOMContentLoaded", () => {
    const qpsBox = document.getElementById("qps-box");
    const overlay = document.getElementById("overlay");
    const qpsButton = document.getElementById("qps-button");
    const closeQps = document.getElementById("close-qps");
    const validateQps = document.getElementById("validate-qps");

    const openSound = new Audio("open.mp3");
    const closeSound = new Audio("close.mp3");

    function openQpsBox() {
        qpsBox.classList.add("active");
        overlay.classList.add("active");
        openSound.play();
    }

    function closeQpsBox() {
        qpsBox.classList.remove("active");
        overlay.classList.remove("active");
        closeSound.play();
    }

    qpsButton.addEventListener("click", openQpsBox);
    closeQps.addEventListener("click", closeQpsBox);
    overlay.addEventListener("click", closeQpsBox);

    document.addEventListener("keydown", (e) => {
        if (e.key === "Escape") {
            closeQpsBox();
        }
    });

    validateQps.addEventListener("click", () => {
        alert("QPS Validé !");
        closeQpsBox();
    });
});




generateLines();
init();
animate();