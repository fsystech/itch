
// 2:54 PM 10/1/2022
const sleep = require('util').promisify(setTimeout);
function _exportMarket() {
    /** @type {NodeJS.Dict<{books:any[]}>} */
    const _order = {
        "123456": {
            books: [{
                order_number: Math.floor(Math.random() * 100000000000),
                verb: "B",
                quantity: 15000,
                price: 1275.20,
                yield: 1,
                executed_quantity: 15000,
                match_order_number: 32562,
                task: ["A", null, "E"]
            }, {
                order_number: Math.floor(Math.random() * 100000000000),
                verb: "S",
                quantity: 10200,
                price: 1272.70,
                yield: 1,
                task: [null, "A", "D"]
            }]
        },
        "123457": {
            books: [{
                order_number: Math.floor(Math.random() * 100000000000),
                verb: "S",
                quantity: 1200,
                price: 15.80,
                yield: 1,
                executed_price: 15.80,
                executed_quantity: 1200,
                match_order_number: Math.floor(Math.random() * 100000000000),
                task: ["A", null, "C"]
            }, {
                order_number: Math.floor(Math.random() * 100000000000),
                verb: "B",
                quantity: 400,
                price: 15.80,
                yield: 1,
                task: [null, "A", "U", "D"]
            }]
        }
    };
    /**
     * @param {number} interval
     * @param {(payload:Buffer)=>boolean} next
     * @param {()=>void} end 
     */
    async function _generator(interval, next, end) {
        if (Object.keys(_order).length === 0) {
            console.log('No rest order book found...');
            return end(-1);
        }
        for (let symbolId in _order) {
            const _symbolId = parseInt(symbolId);
            const { books } = _order[symbolId];
            for (let book of books) {
                if (!Array.isArray(book.task) || book.task.length === 0) continue;
                const task = book.task.shift();
                if (task === null) continue;
                if (!book.symbol_id) {
                    book.symbol_id = _symbolId;
                }
                /** @type {Buffer} */
                let buffer = undefined;
                switch (task) {
                    case 'A': buffer = _newOrderMessage(book); break;
                    case 'E': buffer = _executeOrderMessage(book); break;
                    case 'D': buffer = _deleteOrderMessage(book); break;
                    case 'C': buffer = _executeOrderWithPriceMessage(book); break;
                    case 'U':
                        book.old_order_number = book.order_number;
                        book.order_number = Math.floor(Math.random() * 100000000000);
                        book.quantity += 10;
                        buffer = _replaceOrderMessage(book);
                        break;
                }
                if (!buffer) {
                    console.log(`Unknown task found ${task}`);
                    continue;
                }
                if (!next(buffer)) return;
                await sleep(500);
            }
            let remove = true;
            for (let book of books) {
                if (book.task && book.task.length > 0) {
                    remove = false; break;
                }
            }
            if (remove) {
                console.log(`Removing ${_symbolId}`);
                delete _order[symbolId];
            }
        }
        end(interval + 3000);
    }
    return _generator;
}
/**
 * 
 * @param {import('../lib/Server').Session} session 
 */
function _market(session) {
    let isEnded = false;
    var id = -1;
    function _seystemEvent() {
        id = setInterval(() => {
            if (isEnded) {
                console.log('exitd');
                return;
            }
            session.sendSystemEvent(() => { });
        }, 10000);
    }
    const _generator = _exportMarket();
    function _spin(interval) {
        if (interval < 0) {
            session.sendSystemEvent(() => { });
            _seystemEvent();
            return;
        }
        console.log(`Spin will be wait ${interval}sec for execute`)
        setTimeout(() => {
            _generator(interval, (payload) => {
                if (isEnded) return false;
                session.sendMessage(payload, () => { });
                return true;
            }, _spin);
        }, interval);
    }
    session.on('end', () => {
        isEnded = true;
        console.log('exitd');
        if (id < 0) return;
        clearInterval(id);
    });
    setTimeout(() => {
        if (isEnded) return;
        session.sendSystemEvent(() => { });
    }, 10000);
    _spin(13000);
}
module.exports.market = _market;
const _messageType = {
    new_order: 0x41, // A
    execute_order: 0x45, // E
    executed_with_price: 0x43, // C
    delete_order: 0x44, // D
    replace_order: 0x55, // U
};
/**
 * 
 * @param {number} msgType 
 * @param {number} length 
 */
function _createHeader(msgType, length) {
    const buffer = Buffer.allocUnsafe(length);
    buffer.writeUInt8(msgType, 0);
    const seconds = getMsSinceMidnight(new Date());
    buffer.writeInt32BE(seconds, 1);
    return buffer;
}

function _deleteOrderMessage(obj) {
    const buffer = _createHeader(_messageType.delete_order, 13);
    buffer.writeBigInt64BE(BigInt(obj.order_number), 5);
    console.log(`Message "D" for ${obj.symbol_id}#${obj.order_number} generated; length ${buffer.length}`);
    return buffer;
}
function _replaceOrderMessage(obj) {
    const buffer = _createHeader(_messageType.replace_order, 37);
    buffer.writeBigInt64BE(BigInt(obj.old_order_number), 5);
    buffer.writeBigInt64BE(BigInt(obj.order_number), 13);
    buffer.writeBigInt64BE(BigInt(obj.quantity), 21);
    buffer.writeInt32BE(obj.price * 100, 29);
    buffer.writeInt32BE(obj.yield || 0, 33);
    console.log(`Message "U" for ${obj.symbol_id}#${obj.order_number} generated; length ${buffer.length}`);
    return buffer;
}
function _newOrderMessage(obj) {
    const buffer = _createHeader(_messageType.new_order, 34);
    buffer.writeBigInt64BE(BigInt(obj.order_number), 5);
    buffer.write(obj.verb, 13);
    buffer.writeBigInt64BE(BigInt(obj.quantity), 14);
    buffer.writeInt32BE(obj.symbol_id, 22);
    buffer.writeInt32BE(obj.price * 100, 26);
    buffer.writeInt32BE(obj.yield || 0, 30);
    console.log(`Message "A" for ${obj.symbol_id}#${obj.order_number}#${obj.verb} generated; length ${buffer.length}`);
    return buffer;
}
function _executeOrderMessage(obj) {
    const buffer = _createHeader(_messageType.execute_order, 29);
    buffer.writeBigInt64BE(BigInt(obj.order_number), 5);
    buffer.writeBigInt64BE(BigInt(obj.executed_quantity), 13);
    buffer.writeBigInt64BE(BigInt(obj.match_order_number), 21);
    console.log(`Message "E" for ${obj.symbol_id}#${obj.order_number} generated; length ${buffer.length}`);
    return buffer;
}
function _executeOrderWithPriceMessage(obj) {
    const buffer = _createHeader(_messageType.executed_with_price, 38);
    buffer.writeBigInt64BE(BigInt(obj.order_number), 5);
    buffer.writeBigInt64BE(BigInt(obj.executed_quantity), 13);
    buffer.writeBigInt64BE(BigInt(obj.match_order_number), 21);
    buffer.writeUInt8('Y', 29);
    buffer.writeInt32BE(obj.executed_price * 100, 30);
    buffer.writeInt32BE(obj.symbol_id, 34);
    console.log(`Message "C" for ${obj.symbol_id}#${obj.order_number} generated; length ${buffer.length}`);
    return buffer;
}
function getMsSinceMidnight(d) {
    var e = new Date(d);
    return d - e.setHours(0, 0, 0, 0);
}