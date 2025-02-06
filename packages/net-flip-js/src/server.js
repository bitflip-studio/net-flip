import native from './native.js'

export function createServer({port = 8080} = {}) {
    if(typeof port !== typeof 0) throw new Error(`port must be of type '${typeof 0}', given '${typeof port}'`)
    if(port <= 0 || port > 65535) throw new Error(`port must be between 0 and 65535, given '${port}'`)
    const serverPTR = native.server.alloc();
    if(serverPTR === native.NULL) throw new Error(`failed to allocate server`)
    if(native.server.initFrom(serverPTR, port)) {throw new Error(`failed to initialize server`)}

    const pathMap = new Map()

    /**
     *
     * @param method
     * @param path
     * @param handler
     */
    function attach({method = null, path = null, handler = null} = {}) {
        if(path == null) throw new Error(`path is required, given '${path}'`)
        if(typeof path !== typeof "") throw new Error(`path must be of type '${typeof ''}', given '${typeof path}'`)
        if(method == null) throw new Error(`method is required, given '${method}'`)
        if(typeof method !== typeof "") throw new Error(`method must be of type '${typeof ''}', given '${typeof method}'`)
        if(handler == null) throw new Error(`handler is required, given '${handler}'`)
        if(typeof handler !== typeof (() => {})) throw new Error(`path must be of type '${typeof (() => {})}', given '${typeof handler}'`)
        if(pathMap.has(path)) throw new Error(`path '${path}' is already registered`)

        const pathNativePointer = native.staticString.create()

        pathMap.set(path, {path, handler, encodedPath: encodeURI(path)})
    }

    function start() {

    }
    function stop() {

    }
    return {start, stop, attach}
}

