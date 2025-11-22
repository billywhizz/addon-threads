import { createRequire } from "node:module"

const require = createRequire(import.meta.url)
const { start, stop } = require('./build/Debug/node-addon-api.node')

let count = 0
start(record => {
  count++;
//  console.log(record)
})

setTimeout(() => {
  console.log("stopping")
  console.log(count)
  clearInterval(timer)
  stop() 
}, 5000)

const timer = setInterval(() => console.log(count), 1000)