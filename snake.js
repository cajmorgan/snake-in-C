#!/usr/bin/env node
const snake = require('./build/Release/napi.node')

function playSnake() {
  snake.startGame();
}

playSnake();