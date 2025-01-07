const Module = require('./build/app.js');

Module.onRuntimeInitialized = async () => {
  const map = Module.createImage(4, 4, 1);
  const data = JSON.parse(map);
  console.log(data);
  const map2 = Module.collapseTo(0, 0, "test3");
  const data2 = JSON.parse(map2);
  console.log(data2);
};
