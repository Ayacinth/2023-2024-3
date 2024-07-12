#include <iostream>
#include <unordered_map>
#include <vector>
#include <iomanip>
#include <bits/stdc++.h>

using namespace std;

// 表示投资信息
class Investment 
{
    public:
    
    string name;         // 名称（人名)
    
    string currency;     // 货币类型
    
    int quantity;        // 数量
    
    double price_per_unit;  // 单价
};


// 全局变量
unordered_map<string, double> exchange_rates;  // 存储货币兑换率

unordered_map<string, vector<Investment>> portfolio;  // 存储投资组合


// 函数：添加或更新货币兑换率
void addExchangeRate(string from_currency, string to_currency, double rate) 
{
    exchange_rates[from_currency + to_currency] = rate;
    
    exchange_rates[to_currency + from_currency] = 1.0 / rate;  // 同时存储反向的兑换率
}

// 函数：转换金额为指定货币
double convertAmount(double amount, string from_currency, string to_currency) 
{
    if (from_currency == to_currency) 
    {
        return amount;
    }
    
    double rate = exchange_rates[from_currency + to_currency];
    
    return amount * rate;
}

// 函数：计算指定人的总资产
double calculatePersonAssets(string person_name, string currency) 
{
    double total_assets = 0.0;
    
    if (portfolio.find(person_name) != portfolio.end()) 
    {
        for (const auto& inv : portfolio[person_name]) 
        {
            total_assets += convertAmount(inv.quantity * inv.price_per_unit, inv.currency, currency);
        }
    }
    
    return total_assets;
}


// 函数：计算指定股票的总价值
double calculateStockTotalValue(string stock_name, string currency) 
{
    double total_value = 0.0;
    if (portfolio.find(stock_name) != portfolio.end()) 
    {
        for (const auto& inv : portfolio[stock_name]) 
        {
            total_value += convertAmount(inv.quantity * inv.price_per_unit, inv.currency, currency);
        }
    }
    
    return total_value;
}


int main() {
    // 读取交易记录数量
    int num_transactions;
    
    cin >> num_transactions;
    
    // 处理所有交易记录
    for (int i = 0; i < num_transactions; ++i) 
    {
        string stock_name, name, currency;
        
        int quantity;
        
        double price_per_unit;
        
        // 读取交易记录的类型、名称、货币类型、数量和单价
        cin >> stock_name >> name >> currency >> quantity >> price_per_unit;
        
        // 根据类型将交易信息存入投资组合
        
        Investment inv = {name, currency, quantity, price_per_unit};
        
        /*if (stock_name == "A") {
            portfolio[name].push_back(inv); 
            portfolio[stock_name].push_back(inv); 
        } else if (stock_name == "B") {
            portfolio[name].push_back(inv);  
            portfolio[stock_name].push_back(inv);
        }*/
        
        portfolio[name].push_back(inv);
        
        portfolio[stock_name].push_back(inv);

    }
    
    // 读取货币兑换率数量
    
    int num_exchange_rates;
    
    cin >> num_exchange_rates;
    
    // 处理所有货币兑换率
    
    for (int i = 0; i < num_exchange_rates; ++i) 
    {
        string from_currency, to_currency;
        
        double rate;
        
        cin >> from_currency >> to_currency >> rate;
        
        addExchangeRate(from_currency, to_currency, rate);  // 添加或更新兑换率
    }
    
    // 读取查询数量
    
    int num_queries;
    
    cin >> num_queries;
    
    // 处理所有查询
    double answer[num_queries];
    
    for (int i = 0; i < num_queries; i++) 
    {
        string query_type;
        
        cin>> query_type;
        
        if (query_type == "PERSON") 
        {
            // 查询个人总资产
            string person_name, currency;
            
            cin >> person_name >> currency;
            
            double a = calculatePersonAssets(person_name, currency);
            
            answer[i]=a;
        } 
        else if (query_type == "STOCK") 
        {
            // 查询股票总价值
            
            string stock_name, currency;
            
            cin >> stock_name >> currency;
            
            double total_value = calculateStockTotalValue(stock_name, currency);
            
            answer[i]=total_value;
        }
    }
    
    //输出
    for(int i=0;i<num_queries;i++)
    {
        //cout<<"A"<<i+1<<":"<<floor(answer[i]*100)/100<<endl;
        
        cout<<floor(answer[i]*100)/100<<endl;
    }
    return 0;
}
