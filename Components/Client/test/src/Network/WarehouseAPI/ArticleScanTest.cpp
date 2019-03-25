//
// Created by grosso_a on 16/12/18.
//

#include <gtest/gtest.h>
#include <QApplication>
#include <Network/WarehouseAPI.hpp>
#include <QTimer>
#include <thread>
#include <chrono>
#include <Network/NetworkInfo.hpp>

//!
//! @test Scan article
//!
TEST (ArticleScan, simple)
{
    int     argc = 0;
    char    **argv = nullptr;

    QApplication app(argc, argv);
    cash::network::WarehouseAPI      api(WAREHOUSE_URL, WAREHOUSE_PORT);

    cash::network::ArticleList *articles = api.articles();
    ASSERT_TRUE(articles != nullptr);
}
