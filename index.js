import { createRequire } from "node:module"

const require = createRequire(import.meta.url)
const { start, stop } = require('./build/Release/node-addon-api.node')

start(record => {
  console.log(record)
})

setTimeout(stop, 5000)
