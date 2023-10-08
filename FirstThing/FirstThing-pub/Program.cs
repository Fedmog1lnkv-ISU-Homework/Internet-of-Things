using System.Text.Json;
using MQTTnet;
using MQTTnet.Client;
using MQTTnet.Protocol;

class Program
{
    static async Task Main()
    {
        var mqttClient = await Connect_Client();
        string topicName = "fed-dan";
        await Subscribe_Topic(mqttClient, topicName);
        Console.WriteLine("Enter a message (or 'exit' to quit):");
        while (true)
        {
            var message = Console.ReadLine();

            if (message?.ToLower() == "exit")
                break;

            await Publish_Message(message, mqttClient, topicName);
        }

        await mqttClient.DisconnectAsync();
    }

    public static async Task<MQTTnet.Client.IMqttClient> Connect_Client()
    {
        var mqttFactory = new MqttFactory();
        var mqttClient = mqttFactory.CreateMqttClient();

        var mqttClientOptions = new MqttClientOptionsBuilder().WithTcpServer("broker.emqx.io", 1883).Build();

        await mqttClient.ConnectAsync(mqttClientOptions, CancellationToken.None);

        Console.WriteLine("The MQTT client is connected.");

        return mqttClient;
    }

    public static async Task Subscribe_Topic(IMqttClient mqttClient, string topicName)
    {
        var mqttFactory = new MqttFactory();

        var mqttSubscribeOptions = mqttFactory.CreateSubscribeOptionsBuilder()
            .WithTopicFilter(
                f =>
                {
                    f.WithTopic(topicName);
                })
            .Build();

        var response = await mqttClient.SubscribeAsync(mqttSubscribeOptions, CancellationToken.None);

        Console.WriteLine("MQTT client subscribed to topic.");
    }

    public static async Task Publish_Message(string? message, IMqttClient mqttClient, string topicName)
    {
        var mqttMessage = new MqttApplicationMessageBuilder()
            .WithTopic(topicName)
            .WithPayload(message)
            .WithQualityOfServiceLevel(MqttQualityOfServiceLevel.AtLeastOnce)
            .WithRetainFlag()
            .Build();

        await mqttClient.PublishAsync(mqttMessage, CancellationToken.None);

        Console.WriteLine($"Message published to topic: {message}");
    }
}

internal static class ObjectExtensions
{
    public static TObject DumpToConsole<TObject>(this TObject @object)
    {
        var output = "NULL";
        if (@object != null)
        {
            output = JsonSerializer.Serialize(@object, new JsonSerializerOptions
            {
                WriteIndented = true
            });
        }

        Console.WriteLine($"[{@object?.GetType().Name}]:\r\n{output}");
        return @object;
    }
}
