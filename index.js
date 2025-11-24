import { start, stop } from "./lib/tsfn.js"

function dumpStats () {
  const cpu = process.cpuUsage()
  const user = (cpu.user - prev.user) / 1000 // milliseconds
  const system = (cpu.system - prev.system) / 1000
  const now = performance.now()
  const elapsed = now - then
  console.log(`elapsed ${Math.ceil(elapsed)} count ${count} rss ${process.memoryUsage().rss} usr ${Math.ceil(user / elapsed * 100)} sys ${Math.ceil(system / elapsed * 100)}`)
  count = 0
  then = now
  prev = cpu
}

function onFinish () {
  dumpStats()
//  clearInterval(timer)
  stop()
  console.log('starting again')
  count = 0
  start(_ => count += 1)
  setTimeout(onFinish, 3000)
}

let count = 0
start(_ => count += 1)
setTimeout(onFinish, 3000)
let then = performance.now();
let prev = process.cpuUsage();
const timer = setInterval(dumpStats, 1000)
