import { start, stop } from "./lib/tsfn.js"

let counter = 0
let lastid = 0
let total = 0

function dumpStats () {
  const cpu = process.cpuUsage()
  const user = (cpu.user - prev.user) / 1000 // milliseconds
  const system = (cpu.system - prev.system) / 1000
  const now = performance.now()
  const elapsed = now - then
  console.log(`elapsed ${Math.ceil(elapsed)} counter ${counter} lastid ${lastid} rss ${process.memoryUsage().rss} usr ${Math.ceil(user / elapsed * 100)} sys ${Math.ceil(system / elapsed * 100)}`)
  counter = 0
  then = now
  prev = cpu
}

function onRecord (record) {
  if (record.id - lastid !== 1) throw new Error("Out of Sequence")
  lastid = record.id
//  console.dir(record)
  counter += 1
}

function startRunning () {
  start(onRecord)
  total += 1
  const timer = setInterval(dumpStats, 1000)
  setTimeout(() => stopRunning(timer), 5000)
}

function stopRunning (timer) {
  clearInterval(timer)
  console.log(counter)
  counter = 0
  stop()
  if (total < 3) startRunning()
}

let then = performance.now();
let prev = process.cpuUsage();

startRunning()
