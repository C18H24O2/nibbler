/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 02:07:40 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/06 11:37:24 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Nibbler/Launcher/LaunchOptions.hpp>

#include <Nibbler/Logging/Logger.hpp>
#include <Nibbler/Logging/LoggerFactory.hpp>
#include <Nibbler/Logging/Formatter/DefaultFormatter.hpp>
#include <Nibbler/Logging/Sink/ConsoleSink.hpp>
#include <Nibbler/Launcher/LogMarkers.hpp>

using namespace Nibbler::Launcher;
using namespace Nibbler::Logging;

Logger logger("main");

int main(int argc, char **argv)
{
	auto options = LaunchOptions::Parse(argc, argv);
	if (!options)
		return 1;
	if (options->help)
		return 0;

	std::shared_ptr<IFormatter> formatter = std::make_shared<DefaultFormatter>();
	std::shared_ptr<ISink> consoleSink = std::make_shared<ConsoleSink>(formatter);
	LoggerFactory::Instance().AddConfigurator([&consoleSink, &options](Logger& logger) {
		if (options->verbosity >= 2)
			logger.SetLevel(LogLevel::Trace);
		else if (options->verbosity == 1)
			logger.SetLevel(LogLevel::Debug);
		else
			logger.SetLevel(LogLevel::Info);

		logger.AddSink(consoleSink);
	});
	LoggerFactory::Instance().Reconfigure();

	std::string_view modeName = std::visit([]<typename T>(const T&) -> std::string_view {
		return T::modeName;
	}, options->modeOptions);

	logger.Info().Emit("Launching {} mode", modeName);

	std::visit([&]<typename T>(const T& target) {
		target.CallEntrypoint(*options);
	}, options->modeOptions);
	return 0;
}
