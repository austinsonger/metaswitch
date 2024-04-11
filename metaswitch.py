import time
import json
import websocket

# Configuration
OBS_WEBSOCKET_URL = "ws://localhost:4444"
PASSWORD = "your_password"  # Set this to your OBS WebSocket password
DEVICE_SOURCE_NAMES = ["Camera 1", "Camera 2", "Camera 3"]  # Names of your video capture devices in OBS
SWITCH_INTERVAL = 5  # Time in seconds to display each camera

def send_request(ws, request_type, request_data={}):
    """Send a request to the OBS WebSocket."""
    request_id = "1"
    request = {
        "request-type": request_type,
        "message-id": request_id,
        **request_data
    }
    ws.send(json.dumps(request))

    # Wait for and return the response
    while True:
        response = json.loads(ws.recv())
        if response["message-id"] == request_id:
            return response

def switch_to_next_device(ws, current_device_index):
    """Switch to the next device in the list."""
    next_device_index = (current_device_index + 1) % len(DEVICE_SOURCE_NAMES)
    next_device_name = DEVICE_SOURCE_NAMES[next_device_index]

    # Make all devices invisible
    for device_name in DEVICE_SOURCE_NAMES:
        send_request(ws, "SetSceneItemProperties", {
            "item": device_name,
            "visible": False
        })

    # Make the next device visible
    send_request(ws, "SetSceneItemProperties", {
        "item": next_device_name,
        "visible": True
    })

    return next_device_index

def main():
    ws = websocket.create_connection(OBS_WEBSOCKET_URL)
    
    # Authenticate
    if PASSWORD:
        auth_challenge = send_request(ws, "GetAuthRequired")["challenge"]
        auth_response = send_request(ws, "Authenticate", {"auth": PASSWORD, "challenge": auth_challenge})["auth"]
        if not auth_response:
            print("Authentication failed.")
            ws.close()
            return

    current_device_index = -1
    try:
        while True:
            current_device_index = switch_to_next_device(ws, current_device_index)
            time.sleep(SWITCH_INTERVAL)
    except KeyboardInterrupt:
        pass
    finally:
        ws.close()

if __name__ == "__main__":
    main()
