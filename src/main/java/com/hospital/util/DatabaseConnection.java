package com.hospital.util;

import java.sql.*;

public class DatabaseConnection {
    private static DatabaseConnection instance;
    private Connection connection;

    private DatabaseConnection() throws SQLException {
        this.connection = DriverManager.getConnection("jdbc:h2:mem:hospitaldb", "sa", "");
    }

    public static DatabaseConnection getInstance() throws SQLException {
        if (instance == null) {
            instance = new DatabaseConnection();
        }
        return instance;
    }

    public Connection getConnection() {
        return connection;
    }
}
