/*
** user.c for  in /home/athoma_j/rendu/PSU_2014_myirc
** 
** Made by julien athomas
** Login   <athoma_j@epitech.net>
** 
** Started on  Wed Apr  8 16:02:38 2015 julien athomas
** Last update Wed Apr  8 16:23:27 2015 julien athomas
*/

int	my_pass(char *com, t_client *client)
{
  if (com == NULL)
    {
      write_msg(client, ERR_NEEDMOREPARAMS, "", 3);
      return ;
    }
}
