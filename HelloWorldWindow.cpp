#include <gtkmm.h>
#include <iostream>
#include "DBManager.h" // Include your DBManager header

class AssetManagerWindow : public Gtk::Window {
public:
    AssetManagerWindow() : dbManager("tcp://127.0.0.1:3306", "admin", "password", "WharehouseDB") {
        set_title("Asset Manager");
        set_border_width(10);
        set_default_size(400, 200);

        // Layout
        Gtk::Box *vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
        add(*vbox);

        // TreeView - List of Assets
        assetListStore = Gtk::ListStore::create(assetColumns);
        assetTreeView.set_model(assetListStore);
        assetTreeView.append_column("ID", assetColumns.col_id);
        assetTreeView.append_column("Name", assetColumns.col_name);
        assetTreeView.append_column("Amount", assetColumns.col_amount);
        assetTreeView.append_column("Price", assetColumns.col_price);
        vbox->pack_start(assetTreeView);

        // Add, Remove, Update Buttons
        Gtk::Button *addButton = Gtk::manage(new Gtk::Button("Add"));
        Gtk::Button *removeButton = Gtk::manage(new Gtk::Button("Remove"));
        Gtk::Button *updateButton = Gtk::manage(new Gtk::Button("Update"));
        addButton->signal_clicked().connect(sigc::mem_fun(*this, &AssetManagerWindow::on_add_clicked));
        removeButton->signal_clicked().connect(sigc::mem_fun(*this, &AssetManagerWindow::on_remove_clicked));
        updateButton->signal_clicked().connect(sigc::mem_fun(*this, &AssetManagerWindow::on_update_clicked));
        vbox->pack_start(*addButton);
        vbox->pack_start(*removeButton);
        vbox->pack_start(*updateButton);

        // Load data from the database into the ListStore
        load_assets_from_database();

        // Show all children
        show_all_children();
    }

protected:
    // Signal Handlers
    void on_add_clicked() {
        // Example: Add asset logic
        std::string query = "INSERT INTO asset (name, amount, price) VALUES ('New Asset', 10, 100)";
        dbManager.execute(query);
        load_assets_from_database(); // Refresh the list
    }

    void on_remove_clicked() {
        // Example: Remove asset logic
        // You need to determine which item to remove
    }

    void on_update_clicked() {
        // Example: Update asset logic
        // You need to determine which item to update and the new values
    }

private:
    DBManager dbManager;
    Gtk::TreeView assetTreeView;
    Glib::RefPtr<Gtk::ListStore> assetListStore;
    
    class AssetColumns : public Gtk::TreeModel::ColumnRecord {
    public:
        AssetColumns() { add(col_id); add(col_name); add(col_amount); add(col_price); }

        Gtk::TreeModelColumn<unsigned int> col_id;
        Gtk::TreeModelColumn<Glib::ustring> col_name;
        Gtk::TreeModelColumn<unsigned int> col_amount;
        Gtk::TreeModelColumn<double> col_price;
    } assetColumns;

  void load_assets_from_database() {
      assetListStore->clear();
      std::string query = "SELECT id, name, amount, price FROM asset";
      if (dbManager.execute(query)) {
          sql::ResultSet* results = dbManager.getResults();
          while (results && results->next()) {
              Gtk::TreeModel::Row row = *(assetListStore->append());
              row[assetColumns.col_id] = results->getUInt("id");
              
              // Convert SQLString to std::string, then to Glib::ustring
              std::string name = results->getString("name");
              row[assetColumns.col_name] = Glib::ustring(name);

              row[assetColumns.col_amount] = results->getUInt("amount");
              row[assetColumns.col_price] = results->getDouble("price");
          }
      }
}
};

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example.assetmanager");
    AssetManagerWindow window;
   
    return app->run(window);
}


