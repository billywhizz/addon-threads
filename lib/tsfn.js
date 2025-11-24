import { createRequire } from "node:module"

const require = createRequire(import.meta.url)
const { start, stop } = require('../build/Debug/node-addon-api.node')

export { start, stop }
