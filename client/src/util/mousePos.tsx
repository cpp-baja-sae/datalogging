let mousePos = { x: 0, y: 0, graphStartX: 0, graphEndX: 0 };
export default mousePos;

document.addEventListener('mousemove', event => {
  mousePos.x = event.clientX;
  mousePos.y = event.clientY;
});
