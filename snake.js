#!/usr/bin/env node
const snake = require('./napi.node')

function playSnake() {
  snake.startGame();
}

playSnake();