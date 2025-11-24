import { start, stop } from "./lib/tsfn.js"

let counter = 0
start(() => counter += 1)
setTimeout(() => console.log(counter), 2000)
//setTimeout(stop, 3000)