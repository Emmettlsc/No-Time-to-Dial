// src/App.js
import React, { useState, useEffect } from 'react';
import './App.css';
import MessagesList from './MessagesList';
import DeviceHeader from './DeviceHeader';


function App() {
  const [messages, setMessages] = useState({});
  const [selectedDevice, setSelectedDevice] = useState(null);
  const [editMode, setEditMode] = useState(false);
  const [nameMappings, setNameMappings] = useState({});
  const [newName, setNewName] = useState('');

  const startEdit = (deviceId) => {
    setNewName(nameMappings[deviceId] || '');
    setEditMode(true);
  };

  const saveName = (deviceId, newName) => {
    setNameMappings(prev => ({ ...prev, [deviceId]: newName }));
  };


  useEffect(() => {
    const webSocket = new WebSocket('ws://184.72.14.50:8080/ws');

    webSocket.onmessage = (event) => {
      const message = JSON.parse(event.data);
      const timestamp = Date.now();
      setMessages(prevMessages => ({
        ...prevMessages,
        [message.id]: {
          latestMessage: { text: message.message, timestamp },
          messages: [{ text: message.message, timestamp }, ...(prevMessages[message.id]?.messages || [])]
        }
      }));
    };

    return () => {
      webSocket.close();
    };
  }, []);

  const selectDevice = (deviceId) => {
    setSelectedDevice(deviceId);
  };

  return (
    <div className="App">
      <header className="App-header">
        <h1>Connected Devices</h1>
        {!selectedDevice ? (
          <ul>
            {Object.entries(messages)
              .sort((a, b) => b[1].latestMessage.timestamp - a[1].latestMessage.timestamp)
              .map(([deviceId, deviceMessages]) => (
                <li key={deviceId} onClick={() => selectDevice(deviceId)}>
                  {nameMappings[deviceId] || deviceId} {/* Use the name if available */}
                  <span style={{ fontWeight: 'normal', color: '#666' }}>
                    : {deviceMessages.latestMessage.text}
                  </span>
                </li>
              ))}
          </ul>
        ) : (
          <div>
            <button onClick={() => setSelectedDevice(null)}>Back</button>
            <DeviceHeader
              deviceId={selectedDevice}
              onSave={saveName}
              nameMappings={nameMappings}
            />
            <MessagesList messages={messages[selectedDevice].messages} />
          </div>
        )}
      </header>
    </div>
  );
}

export default App;
