import base64

data = "skoltech{touchd000000000wn}"

encodedBytes = base64.b64encode(data.encode("utf-8"))
encodedStr = str(encodedBytes, "utf-8")

print(encodedStr)

message_bytes = base64.b64decode(encodedBytes)
message = message_bytes.decode('ascii')

print(message)
