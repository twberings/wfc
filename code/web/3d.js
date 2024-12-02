import * as THREE from 'three';
import { OrbitControls } from 'three/addons/controls/OrbitControls.js';
const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
const renderer = new THREE.WebGLRenderer();
const controls = new OrbitControls( camera, renderer.domElement );

camera.position.set( 0, 20, 100 );
controls.update();

const gridHeight = 3;
const gridWidth = 3;
const gridDepth = 3;
const grid = [
  [
    [1, 1, 1],
    [0, 0, 0],
    [0, 0, 0]
  ],
  [
    [1, 1, 1],
    [0, 0, 0],
    [1, 1, 1]
  ],
  [
    [0, 1, 1],
    [1, 0, 1],
    [1, 1, 0]
  ]
]
renderer.setSize(window.innerWidth, window.innerHeight);
renderer.setAnimationLoop(animate);
document.body.appendChild(renderer.domElement);
const geometry = new THREE.BoxGeometry(1, 1, 1);
const material = new THREE.MeshBasicMaterial({
  color: 0x00ff00,
  wireframe: true
});
createGrid(geometry, material);

function animate() {

	requestAnimationFrame( animate );

	// required if controls.enableDamping or controls.autoRotate are set to true

	renderer.render( scene, camera );

}

function createGrid(geometry, material) {
  for (let i = 0; i < gridHeight; i++) {
    for (let j = 0; j < gridWidth; j++) {
      for (let k = 0; k < gridDepth; k++) {
        if (grid[i][j][k] === 1) {
          const newCube = new THREE.Mesh(geometry, material);
          newCube.position.set(i, j, k);
          scene.add(newCube);
        }
      }
    }
  }
}
