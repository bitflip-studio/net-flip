import ffi from 'ffi-napi';
import ref from 'ref-napi'
import path from 'path';

/** @typedef {number} NATIVE_POINTER */

/** @type {NATIVE_POINTER} */
export const NULL = 0

let libcore = null;

export function loadLibrary() {
    libcore = ffi.Library(
        path.resolve(process.cwd(), 'libcore.so'),
        {
            say_hello: [ref.types.void, []],
            VERSION: [ref.types.uint32, []],

            server_alloc: [ref.refType(ref.types.void), []],
            server_init: [ref.types.int32, [ref.refType(ref.types.void)]],
            server_init_fromArgs: [ref.types.int32, [ref.types.uint16]],
            staticString_create: [ref.refType(ref.types.void), [ref.types.uint32, ref.refType(ref.types.uint8)]],
        }
    );
}

export function sayHello() {
    libcore.say_hello();
}

/**
 * @param {number} encodedVersion
 * @returns {{major: number, minor: number, patch: number}}
 */
function decodeVersion(encodedVersion) {
    return {
        major: (encodedVersion >> 24) & 0xFF,   // Extracts the highest byte
        minor: (encodedVersion >> 16) & 0xFF,   // Extracts the second byte
        patch: encodedVersion & 0xFFFF          // Extracts the lowest 2 bytes
    };
}

/**
 * Retrieves and decodes the encoded version from the native library.
 *
 * @returns {{ major: number, minor: number, patch: number }}
 * An object containing the major, minor, and patch version numbers.
 */
export function VERSION() {
    return decodeVersion(libcore.VERSION());
}

/**
 * @returns {NATIVE_POINTER}
 */
function server_alloc() {
    return libcore.server_alloc();
}

/**
 * initialize a server in an allocated memory region (will allocate more memory for streams and event loop)
 * @param {NATIVE_POINTER} serverPTR
 * @param {NATIVE_POINTER} settingsPTR
 * @returns {boolean}
 */
function server_init(serverPTR, settingsPTR) {
    return libcore.server_init(serverPTR, settingsPTR) !== 0;
}

/**
 * initialize a server in an allocated memory region (will allocate more memory for streams and event loop)
 * @param {NATIVE_POINTER} serverPTR
 * @param {number} port
 * @returns {boolean}
 */
function server_init_fromArgs(serverPTR, port) {
    return libcore.server_init_fromArgs(serverPTR, port) !== 0;
}

/**
 *
 * @param {number} size
 * @param {string} str
 * @returns {NATIVE_POINTER}
 */
function staticString_create(size, str) {
    return libcore.staticString_create(size, str);
}

export const staticString = {
    create: staticString_create,
}

export const server = {
    alloc: server_alloc,
    init: server_init,
    initFrom: server_init_fromArgs,
}

export default {loadLibrary, sayHello, VERSION, server, NULL, staticString};

