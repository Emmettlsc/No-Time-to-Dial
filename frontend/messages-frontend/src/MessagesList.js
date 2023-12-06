// src/MessagesList.js
import React from 'react';

function MessagesList({ messages }) {
    return (
        <div>
            {messages.map((message, index) => (
                <div key={index}>
                    <strong>{new Date(message.timestamp).toLocaleString()}:</strong> {message.text}
                </div>
            ))}
        </div>
    );
}

export default MessagesList;
