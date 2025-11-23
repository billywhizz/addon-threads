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

let then = performance.now();
let prev = process.cpuUsage();

const timer = setInterval(() => {
  const cpu = process.cpuUsage();
  const user = (cpu.user - prev.user) / 1000; // milliseconds
  const system = (cpu.system - prev.system) / 1000;
  const now = performance.now()
  const elapsed = now - then
  console.log(`count ${count} rss ${process.memoryUsage().rss} usr ${Math.ceil(user / elapsed * 100)} sys ${Math.ceil(system / elapsed * 100)}`)
  count = 0
  then = now
  prev = cpu;
}, 1000)