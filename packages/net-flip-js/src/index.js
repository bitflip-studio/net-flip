import nativeApi from "./native.js"


nativeApi.loadLibrary()
nativeApi.sayHello()

console.log(`Loaded version: ${JSON.stringify(nativeApi.VERSION())}`)