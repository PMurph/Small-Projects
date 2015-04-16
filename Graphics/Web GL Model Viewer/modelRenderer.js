var gl;

function initModelRenderer(canvas) {
    if(!canvas) {
        throw "Cannot initialize model renderer without a valid canvas element";
    }
    
    gl = canvas.getContext("experimental-webgl");
    
    if(!gl) {
        throw "Error occured when creating WebGL context";
    }
    
    gl.viewportWidth = canvas.width;
    gl.viewportHeight = canvas.height;
}