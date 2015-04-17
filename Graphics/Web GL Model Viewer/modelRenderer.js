var gl;
var shaderProgram;
var mvMatrix;
var pMatrix;

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

function initShaders() {
    var fragmentShader = getShader("frag_shader");
    var vertexShader = getShader("vert_shader");

    if(!fragmentShader || !vertexShader) {
        return null;
    }

    shaderProgram = gl.createProgram();
    gl.attachShader(shaderProgram, vertexShader);
    gl.attachShader(shaderProgram, fragmentShader);
    gl.linkProgram(shaderProgram);

    if(!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS)) {
        console.log("Could not link shader program");
        return null;
    }

    gl.useProgram(shaderProgram);

    shaderProgram.vertexPositionAttribute = gl.getAttribLocation(shaderProgram, "aVertexPosition");
    gl.enableVertexAttribArray(shaderProgram.vertexPositionAttribute);

    shaderProgram.pMatrixUniform = gl.getUniformLocation(shaderProgram, "uPMatrix");
    shaderProgram.mvMatrixUniform = gl.getUniformLocation(shaderProgram, "uMVMatrix");
}

function getShader(id) {
    var shaderScript = document.getElementById(id);
    if(!shaderScript) {
        console.log("Could not get shader with id=" + id);
        return null;
    }

    var shaderSrc = "";
    var shaderSrcNode = shaderScript.firstChild;
    while(shaderSrcNode) {
        if(shaderSrcNode.nodeType = 3) {
            shaderSrc += shaderSrcNode.textContent;
        } else {
            console.log("Found invalid node type " + shaderSrcNode.nodeType + " in shader with id=" + id);
        }
        shaderSrcNode = shaderSrcNode.nextSibling;
    }
                
    var shader;
    if(shaderScript.type == "x-shader/x-fragment") {
        shader = gl.createShader(gl.FRAGMENT_SHADER);
    } else if(shaderScript.type == "x-shader/x-vertex") {
        shader = gl.createShader(gl.VERTEX_SHADER);
    } else {
        console.log("Shader script with id=" + id + " is not a valid type: " + shaderScript.type);
        return null;
    }

    gl.shaderSource(shader, shaderSrc);
    gl.compileShader(shader);

    if(!gl.getShaderParameter(shader, gl.COMPILE_STATUS)){
        console.log(gl.getShaderInfoLog(shader));
        return null;
    }

    return shader;
}

function initMatrices() {
    pMatrix = mat4.create();
    mvMatrix = mat4.create();
}

function createBufferFromVertices(vertices, drawType, numVerticesPerItem, numItems) {
    var buffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, buffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
    buffer.drawType = drawType;
    buffer.numVerticesPerItem = numVerticesPerItem;
    buffer.numItems = numItems;
    return buffer;
}

function initScene() {
    gl.viewport(0, 0, gl.viewportWidth, gl.viewportHeight);
    
    mat4.perspective(45, gl.viewportWidth / gl.viewportHeight, 0.1, 100.0, pMatrix);
}

function drawScene() {
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    for(var index in sceneObjects) {
        mvMatrix = sceneObjects[index].modelViewMatrix;
        gl.bindBuffer(gl.ARRAY_BUFFER, sceneObjects[index].buffer);
        gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, sceneObjects[index].buffer.numVerticesPerItem, gl.FLOAT, false, 0, 0);
        setMatrixUniforms();
        gl.drawArrays(sceneObjects[index].buffer.drawType, 0, sceneObjects[index].buffer.numItems);
    }
}