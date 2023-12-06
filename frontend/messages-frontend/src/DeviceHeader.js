import React, { useState } from 'react';

function DeviceHeader({ deviceId, onSave, nameMappings }) {
  const [editMode, setEditMode] = useState(false);
  const [newName, setNewName] = useState(nameMappings[deviceId] || '');

  const handleSave = () => {
    onSave(deviceId, newName);
    setEditMode(false);
  };

  return (
    <div>
      {editMode ? (
        <>
          <input
            type="text"
            value={newName}
            onChange={e => setNewName(e.target.value)}
          />
          <button onClick={handleSave}>Save</button>
        </>
      ) : (
        <>
          <span>{nameMappings[deviceId] || deviceId}</span>
          <button onClick={() => setEditMode(true)}>Edit</button>
        </>
      )}
    </div>
  );
}

export default DeviceHeader;