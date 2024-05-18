/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-05-14 14:05:51
 * @LastEditors: Clark
 * @LastEditTime: 2024-05-18 13:07:54
 * @Description: file content
 */

#include <thread>
#include <pcl/visualization/cloud_viewer.h>
#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>


bool show_pointcloud(pcl::visualization::PCLVisualizer& viewer, pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud)
{
    static bool first = true;
    if (first)
    {
        first = false;
        viewer.addPointCloud(cloud);
    }
    else
    {
        viewer.updatePointCloud(cloud);
    }
    viewer.spin ();

    return true;
}

bool show_pointcloud(pcl::visualization::PCLVisualizer& viewer, pcl::PointCloud<pcl::PointXYZRGBA>::Ptr& cloud)
{
    static bool first = true;
    if (first)
    {
        first = false;
        viewer.addPointCloud(cloud);
    }
    else
    {
        viewer.updatePointCloud(cloud);
    }
    viewer.spin ();

    return true;
}

bool add_color_handler(pcl::visualization::PCLVisualizer& viewer, pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud)
{
    pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZ> color_handler(cloud, "z");
    viewer.addPointCloud(cloud, color_handler, "my_cloud");

    // 从可视化器中获取点云数据
    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr saved_cloud(new pcl::PointCloud<pcl::PointXYZRGBA>);
    // viewer.saveCloud("my_cloud", saved_cloud);
    // viewer.updatePointCloud<pcl::PointXYZRGBA>("my_cloud", *saved_cloud);
    // viewer.updatePointCloud<pcl::PointXYZ>("my_cloud", *cloud);

    // 保存点云到PCD文件
    pcl::io::savePCDFileASCII("saved_cloud.pcd", *saved_cloud);
    return true;
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " cloud.pcd" << std::endl;
        return -1;
    }

    pcl::visualization::PCLVisualizer viewer("viewer");

    pcl::PointCloud<pcl::PointXYZ>::Ptr xyzCloud (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr xyzrgbCloud (new pcl::PointCloud<pcl::PointXYZRGBA>);

    if (pcl::io::loadPCDFile<pcl::PointXYZ>(argv[1], *xyzCloud) != -1)
    {
        std::cout << "show_pointcloud xyzCloud: " << argv[1] << std::endl;
        // add_color_handler(viewer, xyzCloud);
        show_pointcloud(viewer, xyzCloud);
    }
    else if (pcl::io::loadPCDFile<pcl::PointXYZRGBA>(argv[1], *xyzrgbCloud) != -1)
    {
        std::cout << "show_pointcloud xyzrgbCloud: " << argv[1] << std::endl;
        show_pointcloud(viewer, xyzrgbCloud);
    }
    else
    {
        std::cout << "Cloud format not supported." << std::endl;
        return -1;
    }

    // viewer.getRenderWindow()->Render(); // 未启动交互器，不能拖动点云图
    // while (!viewer.wasStopped ())
    // {
    //     std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    //     std::this_thread::yield ();
    // }
    return 0;
}

