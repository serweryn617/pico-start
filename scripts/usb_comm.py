import usb.core
import usb.util
import time

dev = usb.core.find(idVendor=0xcafe, idProduct=0x4014)

if dev is None:
    raise ValueError('Device not found')

# Detach HID driver
for cfg in dev:
    for intf in cfg:
        if dev.is_kernel_driver_active(intf.bInterfaceNumber):
            dev.detach_kernel_driver(intf.bInterfaceNumber)

dev.set_configuration()
cfg = dev.get_active_configuration()

# Get endpoints
intr_intf = None
bulk_intf = None

for intf in cfg:
    usb.util.claim_interface(dev, intf.bInterfaceNumber)
    for ep in intf:
        if usb.util.endpoint_type(ep.bmAttributes) == usb.util.ENDPOINT_TYPE_INTR:
            intr_intf = intf
        if usb.util.endpoint_type(ep.bmAttributes) == usb.util.ENDPOINT_TYPE_BULK:
            bulk_intf = intf
    if intr_intf and bulk_intf:
        break

ep_intr_out = usb.util.find_descriptor(
    intr_intf,
    custom_match = (
        lambda e:
            usb.util.endpoint_direction(e.bEndpointAddress) == usb.util.ENDPOINT_OUT
        )
    )

ep_bulk_out = usb.util.find_descriptor(
    bulk_intf,
    custom_match = (
        lambda e:
            usb.util.endpoint_direction(e.bEndpointAddress) == usb.util.ENDPOINT_OUT
        )
    )

# Measure throughput
TOTAL_BYTES = 1 * 1024 * 1024  # 1 MiB
PAYLOAD = bytes([0xC6]) * TOTAL_BYTES
TIMEOUT_MS = 20000

print("Testing bulk endpoint")

start = time.perf_counter()
wrote = ep_bulk_out.write(PAYLOAD, TIMEOUT_MS)
if wrote != TOTAL_BYTES:
    raise IOError(f"Short write: expected {TOTAL_BYTES}, wrote {wrote}")
end = time.perf_counter()

elapsed = end - start
mib = TOTAL_BYTES / (1 * 1024 * 1024)
mibs = mib / elapsed
mbps = (TOTAL_BYTES * 8) / (1_000_000 * elapsed)

print(f"Wrote {mib:.2f} MiB in {elapsed:.4f} s")
print(f"Throughput: {mibs:.2f} MiB/s ({mbps:.2f} Mbit/s)")


print()
print("Testing interrupt endpoint")

start = time.perf_counter()
wrote = ep_intr_out.write(PAYLOAD, TIMEOUT_MS)
if wrote != TOTAL_BYTES:
    raise IOError(f"Short write: expected {TOTAL_BYTES}, wrote {wrote}")
end = time.perf_counter()

elapsed = end - start
kib = TOTAL_BYTES / (1 * 1024)
kibs = kib / elapsed
kbps = (TOTAL_BYTES * 8) / (1_000 * elapsed)

print(f"Sent {kib:.2f} KiB in {elapsed:.4f} s")
print(f"Throughput: {kibs:.2f} KiB/s ({kbps:.2f} Kbit/s)")
