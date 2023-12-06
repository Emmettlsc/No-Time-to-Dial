//
//  ContentView.swift
//  No Time To Dial Watch App
//
//  Created by Emmett Cocke on 11/18/23.
//

import SwiftUI

struct ContentView: View {
    @EnvironmentObject var model: ItemListModel

    var body: some View {
        NavigationView {
            List(model.devices.keys.sorted(), id: \.self) { deviceUUID in
                NavigationLink(destination: MessageDetailView(deviceUUID: deviceUUID, messages: model.devices[deviceUUID] ?? [])) {
                    Text(model.deviceNames[deviceUUID] ?? "Device: \(deviceUUID)")
                }
            }
            .navigationTitle("Connected Devices")
        }
    }
}


struct MessageDetailView: View {
    var deviceUUID: String
    var messages: [TimestampedMessage]
    @EnvironmentObject var model: ItemListModel

    var body: some View {
        List(messages, id: \.id) { timestampedMessage in
            VStack(alignment: .leading) {
                Text(timestampedMessage.message)
                Text("\(timestampedMessage.timestamp, formatter: dateFormatter)")
                    .font(.caption)
                    .foregroundColor(.gray)
            }
        }
        .navigationTitle("Messages from \(model.deviceNames[deviceUUID] ?? deviceUUID)")
    }

    private var dateFormatter: DateFormatter {
        let formatter = DateFormatter()
        formatter.dateStyle = .short
        formatter.timeStyle = .short
        return formatter
    }
}
#Preview {
    ContentView()
}
