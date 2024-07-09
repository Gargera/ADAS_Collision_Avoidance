# subscriber.py
import paho.mqtt.client as mqtt

broker_address = "192.168.1.32"  # Replace with the broker's IP address
topic = "test/topic"

def on_message(client, userdata, message):
    print(f"Received message: {str(message.payload.decode('utf-8'))} on topic {message.topic}")

client = mqtt.Client("SubscriberClient")
client.connect(broker_address)

client.subscribe(topic)
client.on_message = on_message

client.loop_forever()
