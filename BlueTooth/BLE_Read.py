import asyncio
from bleak import BleakClient

buffer = ""
lines_cache = []

def notification_handler(sender, data):
    global buffer, lines_cache
    try:
        text = data.decode(errors="ignore")
        buffer += text

        while '\r\n' in buffer:
            line, buffer = buffer.split('\r\n', 1)
            line = line.strip()
            if line:
                lines_cache.append(line)

            if len(lines_cache) == 4:
                for l in lines_cache:
                    print(l)
                print()
                lines_cache.clear()

    except Exception as e:
        print(f"Error decoding: {e}")

async def listen_notify(address, notify_uuid):
    async with BleakClient(address) as client:
        await client.start_notify(notify_uuid, notification_handler)
        print("Listening ...")
        await asyncio.sleep(10)
        await client.stop_notify(notify_uuid)

device_address = "CB10FD5E-F4D9-D8F8-6821-C11B34CA054B"
notify_uuid = "0000ffe1-0000-1000-8000-00805f9b34fb"
asyncio.run(listen_notify(device_address, notify_uuid))