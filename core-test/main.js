// index.js
import ffi from 'ffi-napi';
import path from 'path';

// Define the function signature for say_hello: returns void and takes no arguments.
const libcore = ffi.Library(
    path.resolve(process.cwd(), 'libcore.so'),
    {
        say_hello: ['void', []],
    }
);

// Call the function
libcore.say_hello();