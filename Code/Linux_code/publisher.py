# publisher.py
import paho.mqtt.client as mqtt

broker_address = "192.168.1.30"  # Replace with the broker's IP address
topic = "test/topic"

client = mqtt.Client("PublisherClient")
client.connect(broker_address)

message = "Hello from Publisher!"
client.publish(topic, message)
print(f"Published: {message}")

client.disconnect()
