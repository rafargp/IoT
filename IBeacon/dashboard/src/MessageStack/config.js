export default {
    // MQTT servers websocket connection
    port: 1883,
    host: 'brware.com.br',
    username: 'brware',
    password: 'SQRT(pi)!=314',
    clientId: 'bledemo_' + Math.random().toString(16).substr(2, 8),
    channel: '/beacons/office'
};
