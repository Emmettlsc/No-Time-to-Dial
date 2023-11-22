//
//  ContentView.swift
//  No Time To Dial Watch App
//
//  Created by Emmett Cocke on 11/18/23.
//

import SwiftUI

struct ContentView: View {
    @EnvironmentObject private var model: ItemListModel

    var body: some View {
        List {
            ForEach(model.items.keys.sorted(), id: \.self) { key in
                Section(header: Text("Sender: \(key)")) {
                    Text(model.items[key] ?? "")
                }
            }
            
            if model.items.isEmpty {
                Text("No Current Messages")
                    .foregroundStyle(.gray)
            }
        }
        .navigationTitle("Connections")
    }
}


#Preview {
    ContentView()
}
